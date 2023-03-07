# pragma once

# include <cstdint>
# include <string>

namespace Yk::Core
{
    /*
        UString

        - Mutable UTF16 string
        - Easily convertable to UTF8 (Multi-byte)
    */
    class UString final
    {
    public:
        static constexpr uint64_t NPOS = ~( 0llu );

    public:
        constexpr UString::UString() = default;
        UString( const UString & other );
        constexpr UString( UString && other );
        UString( const char16_t * tag );
        UString( const char16_t * tag, uint64_t length );
        UString( const std::string_view & tag );
        ~UString();

        UString & operator = ( const UString & other );
        constexpr UString & operator = ( UString && other );

        constexpr const char16_t * CStr() const { return m_Buf; }
        constexpr operator const char16_t * () { return CStr(); }

        constexpr uint64_t Length() const { return m_Length; }
        constexpr uint64_t Capacity() const { return m_Capacity; }

        const char * ToMultiByte() const;
        inline operator const char * () const { return ToMultiByte(); }

        bool operator == ( const UString & other ) const;
        inline bool operator != ( const UString & other ) const { return !( *this == other ); }

        UString & Append( const char16_t * tag );
        inline UString & operator += ( const char16_t * tag ) { return Append( tag ); }

        UString & ToLower();
        UString & ToUpper();
        uint64_t Find( const char16_t * tag, uint64_t pos = 0 ) const;
        UString SubStr( uint64_t pos, uint64_t length = UString::NPOS ) const;

        void Reserve( uint64_t length );

        inline bool Contains( const char16_t * tag, uint64_t pos = 0 ) const { return Find( tag, pos ) != UString::NPOS; }
        constexpr bool Empty() const { return m_Length == 0; }

        constexpr const char16_t & operator [] ( uint64_t pos ) const;

    private:
        char16_t * m_Buf{ nullptr };
        uint64_t m_Length{ 0 };
        uint64_t m_Capacity{ 0 };

        struct MultiByteCache
        {
            char * m_Buf{ nullptr };
            bool m_Dirty{ false };

            constexpr MultiByteCache() = default;
            MultiByteCache( const MultiByteCache & ) = delete;
            constexpr MultiByteCache( MultiByteCache && other );

            constexpr MultiByteCache & operator = ( MultiByteCache && other );
        };
        mutable MultiByteCache m_MultiByteCache;
    };

    constexpr UString::UString( UString && other )
        : m_Buf{ other.m_Buf }
        , m_Length{ other.m_Length }
        , m_Capacity{ other.m_Capacity }
        , m_MultiByteCache{ std::move( other.m_MultiByteCache ) }
    {
        other.m_Buf = nullptr;
        other.m_Length = 0;
        other.m_Capacity = 0;
    }

    constexpr UString & UString::operator = ( UString && other )
    {
        if( m_Buf )
            delete[] m_Buf;

        m_Buf = other.m_Buf;
        m_Length = other.m_Length;
        m_Capacity = other.m_Capacity;
        m_MultiByteCache = std::move( other.m_MultiByteCache );

        other.m_Buf = nullptr;
        other.m_Length = 0;
        other.m_Capacity = 0;

        return *this;
    }

    constexpr UString::MultiByteCache::MultiByteCache( MultiByteCache && other )
        : m_Buf{ other.m_Buf }
        , m_Dirty{ other.m_Dirty }
    {
        other.m_Buf = nullptr;
        other.m_Dirty = false;
    }

    constexpr UString::MultiByteCache & UString::MultiByteCache::operator = ( MultiByteCache && other )
    {
        if( m_Buf )
            delete[] m_Buf;

        m_Buf = other.m_Buf;
        m_Dirty = other.m_Dirty;

        other.m_Buf = nullptr;
        other.m_Dirty = false;

        return *this;
    }

    constexpr const char16_t & UString::operator [] ( uint64_t pos ) const
    {
        return *( m_Buf + pos );
    }

# if defined( TEXT )
# undef TEXT
# endif

# define TEXT( tag ) u##tag

}
