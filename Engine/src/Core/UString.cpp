# include "UString.h"

# include <uchar.h>

namespace Yk::Core
{
    namespace Helpers
    {
        template <typename CharType>
        constexpr uint64_t StrLen( const CharType * tag )
        {
            auto p{ tag };
            while ( *p++ ) {}
            return ( p - 1 ) - tag; // -1 for '\0'
        }

        char16_t * MultiByteToUTF16(
            const std::string_view & tag,
            uint64_t & outCapacity,
            uint64_t & outLength
        )
        {
            if( tag.empty() )
                return nullptr;

            auto tmpCapacity{ tag.length() };
            auto tmpLength{ 0llu };

            auto tmpBuf{ new char16_t[ tmpCapacity ] };

            char16_t out{};
            mbstate_t state{};
            auto p{ tag.data() };
            while( *p )
            {
                const auto res{ mbrtoc16( &out, p++, MB_CUR_MAX, &state )};
                if( res > 0 && res <= MB_CUR_MAX )
                    *( tmpBuf + tmpLength++ ) = out;
            }

            outCapacity = tmpLength + 1; // +1 for '\0'
            outLength = tmpLength;

            auto buf{ new char16_t[ outCapacity ] };
            memcpy( buf, tmpBuf, tmpLength * sizeof( char16_t ) );
            buf[ outLength ] = u'\0';
            delete[] tmpBuf;

            return buf;
        }

        char * UTF16ToMultiByte(
            const char16_t * tag,
            uint64_t length,
            uint64_t & outCapacity,
            uint64_t & outLength
        )
        {
            static constexpr size_t c_InvalidRes = static_cast<size_t>( -1 );

            if( !tag )
                return nullptr;

            // Single code unit in UTF16 can expand to at most three in multi-byte, and a
            // code point that takes two code units in UTF16 will always take four
            // code units in UTF8. Therefore the maximum number of characters we need
            // to store is 3 per char.
            auto tmpCapacity = length * 3;
            auto tmpLength = 0llu;

            auto tmpBuf{ new char[ tmpCapacity ] };

            char out[ MB_LEN_MAX ];
            mbstate_t state{};
            auto p{ tag };
            while( *p )
            {
                const auto res{ c16rtomb( out, *p++, &state )};
                if( res > 0 && res != c_InvalidRes )
                {
                    memcpy( tmpBuf + tmpLength, out, res );
                    tmpLength += static_cast<uint64_t>( res );
                }
            }

            outCapacity = tmpLength + 1; // +1 for '\0'
            outLength = tmpLength;

            auto buf{ new char[ outCapacity ] };
            memcpy( buf, tmpBuf, tmpLength );
            buf[ outLength ] = '\0';
            delete[] tmpBuf;

            return buf;
        }
    }

    UString::UString( const UString & other )
        : m_Buf{ nullptr }
        , m_Length{ other.m_Length }
        , m_Capacity{ other.m_Capacity }
        , m_MultiByteCache{}
    {
        if( other.m_Buf )
        {
            m_Buf = new char16_t[ m_Capacity ];
            memcpy( m_Buf, other.m_Buf, m_Capacity * sizeof( char16_t ) );
        }
    }

    UString::UString( const char16_t * tag )
        : m_Buf{ nullptr }
        , m_Length{ 0 }
        , m_Capacity{ 0 }
        , m_MultiByteCache{}
    {
        if( !tag )
            return;

        m_Length = Helpers::StrLen( tag );
        m_Capacity = m_Length + 1; // +1 for '\0'
        m_Buf = new char16_t[ m_Capacity ];
        memcpy( m_Buf, tag, m_Capacity * sizeof( char16_t ) );

        m_MultiByteCache.m_Dirty = true;
    }

    UString::UString( const char16_t * tag, uint64_t length )
        : m_Buf{ nullptr }
        , m_Length{ 0 }
        , m_Capacity{ 0 }
        , m_MultiByteCache{}
    {
        if( !tag )
            return;

        m_Length = std::min( Helpers::StrLen( tag ), length );
        m_Capacity = m_Length + 1; // +1 for '\0'
        m_Buf = new char16_t[ m_Capacity ];
        memcpy( m_Buf, tag, m_Capacity * sizeof( char16_t ) );
        m_Buf[ m_Length ] = u'\0';

        m_MultiByteCache.m_Dirty = true;
    }

    UString::UString( const std::string_view & tag )
        : m_Buf{ nullptr }
        , m_Length{ 0 }
        , m_Capacity{ 0 }
        , m_MultiByteCache{}
    {
        if( tag.empty() )
            return;

        m_Buf = Helpers::MultiByteToUTF16( tag, m_Capacity, m_Length );
        m_MultiByteCache.m_Dirty = true;
    }

    UString::~UString()
    {
        if( m_Buf )
            delete[] m_Buf;

        if( m_MultiByteCache.m_Buf )
            delete[] m_MultiByteCache.m_Buf;
    }

    UString & UString::operator = ( const UString & other )
    {
        if( m_Buf )
            delete[] m_Buf;

        m_Buf = nullptr;
        m_Length = other.m_Length;
        m_Capacity = other.m_Capacity;
        m_MultiByteCache.m_Dirty = true;

        if( other.m_Buf )
        {
            m_Buf = new char16_t[ m_Capacity ];
            memcpy( m_Buf, other.m_Buf, m_Capacity * sizeof( char16_t ) );
        }

        return *this;
    }

    const char * UString::ToMultiByte() const
    {
        if( m_MultiByteCache.m_Dirty )
        {
            // OPTIMIZATION: We could avoid a reallocation if we track
            // the current capacity of the cache.

            if( m_MultiByteCache.m_Buf )
                delete[] m_MultiByteCache.m_Buf;

            uint64_t dummyCapacity, dummyLength;

            m_MultiByteCache.m_Buf = Helpers::UTF16ToMultiByte(
                m_Buf,
                m_Length,
                dummyCapacity,
                dummyLength
            );

            m_MultiByteCache.m_Dirty = false;
        }

        return m_MultiByteCache.m_Buf;
    }

    bool UString::operator == ( const UString & other ) const
    {
        if( m_Length != other.m_Length )
            return false;

        return memcmp( m_Buf, other.m_Buf, m_Length * sizeof( char16_t )) == 0
            ? true
            : false;
    }

    UString & UString::Append( const char16_t * tag )
    {
        const auto tagLength{ Helpers::StrLen( tag ) };

        if( m_Length + tagLength < m_Capacity )
        {
            memcpy( m_Buf + m_Length, tag, tagLength * sizeof( char16_t ));
            m_Length += tagLength;
            m_Buf[ m_Length ] = u'\0';
        }
        else
        {
            Reserve( m_Length + tagLength );

            memcpy( m_Buf + m_Length, tag, tagLength * sizeof( char16_t ) );
            m_Length += tagLength;
            m_Buf[ m_Length ] = u'\0';
        }

        m_MultiByteCache.m_Dirty = true;

        return *this;
    }

    UString & UString::ToLower()
    {
        auto p{ m_Buf };
        while( *p )
        {
            *p = ::towlower( *p );
            p++;
        }
        m_MultiByteCache.m_Dirty = true;
        return *this;
    }

    UString & UString::ToUpper()
    {
        auto p{ m_Buf };
        while( *p )
        {
            *p = ::towupper( *p );
            p++;
        }
        m_MultiByteCache.m_Dirty = true;
        return *this;
    }

    uint64_t UString::Find( const char16_t * tag, uint64_t pos ) const
    {
        if( pos > ( m_Length - 1 ))
            return UString::NPOS;

        const auto tagLen{ Helpers::StrLen( tag ) };

        auto p{ m_Buf + pos };
        while( *p )
        {
            if( tagLen > ( m_Length - ( p - m_Buf )))
                break;

            if( memcmp( p, tag, tagLen ) == 0 )
                return static_cast<uint64_t>( p - m_Buf );

            ++p;
        }

        return UString::NPOS;
    }

    UString UString::SubStr( uint64_t pos, uint64_t length ) const
    {
        if( pos > ( m_Length - 1 ))
            return {};

        const auto len{ std::min( length, m_Length - pos ) };
        return { m_Buf + pos, len };
    }

    void UString::Reserve( uint64_t length )
    {
        if( length < m_Capacity )
            return;

        m_Capacity = length + 1; // +1 for '\0'
        auto buf{ new char16_t[ m_Capacity ] };
        memcpy( buf, m_Buf, m_Length * sizeof( char16_t ) );
        buf[ m_Length ] = u'\0';

        delete[] m_Buf;
        m_Buf = buf;
    }

    void UString::Resize( uint64_t length, char16_t c )
    {
        if( length == m_Length && ( m_Length + 1 ) == m_Capacity )
            return;

        if( length > m_Length )
        {
            Reserve( length );

            auto p{ m_Buf + m_Length };
            auto count = length - m_Length;
            while( count-- )
                *p++ = c;
        }
        else
        {
            m_Capacity = length + 1; // +1 for '\0'
            auto buf{ new char16_t[ m_Capacity ] };
            memcpy( buf, m_Buf, length * sizeof( char16_t ) );
            buf[ length ] = u'\0';

            delete[] m_Buf;
            m_Buf = buf;
        }

        m_Length = length;
        m_MultiByteCache.m_Dirty = true;
    }
}
