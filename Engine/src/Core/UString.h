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
        UString::UString() = default;
        UString( const UString & other );
        UString( UString && other );
        UString( const char16_t * tag );
        UString( const char16_t * tag, uint64_t length );
        UString( const std::string_view & tag );
# if defined( YK_PLATFORM_WINDOWS )
        UString( const wchar_t * tag );
# endif
        ~UString();

        UString & operator = ( const UString & other );
        UString & operator = ( UString && other );

        const char16_t * CStr() const { return m_Buf; }
        operator const char16_t * () { return CStr(); }

        uint64_t Length() const { return m_Length; }
        uint64_t Capacity() const { return m_Capacity; }

        const char * ToMultiByte() const;
        inline operator const char * () const { return ToMultiByte(); }

        bool operator == ( const UString & other ) const;
        inline bool operator != ( const UString & other ) const { return !( *this == other ); }

        UString & Append( const char16_t * tag );
        inline UString & operator += ( const char16_t * tag ) { return Append( tag ); }

        UString & ToLower();
        UString & ToUpper();
        uint64_t Find( const char16_t * tag, uint64_t pos = 0 ) const;
        uint64_t FindLastOf( const char16_t * tag, uint64_t pos = UString::NPOS ) const;
        UString SubStr( uint64_t pos, uint64_t length = UString::NPOS ) const;

        void Reserve( uint64_t length );
        void Resize( uint64_t length, char16_t c = '\0' );

        inline bool Contains( const char16_t * tag, uint64_t pos = 0 ) const { return Find( tag, pos ) != UString::NPOS; }
        bool Empty() const { return m_Length == 0; }

        const char16_t & operator [] ( uint64_t pos ) const;

    private:
        char16_t * m_Buf{ nullptr };
        uint64_t m_Length{ 0 };
        uint64_t m_Capacity{ 0 };

        struct MultiByteCache
        {
            char * m_Buf{ nullptr };
            bool m_Dirty{ false };

            MultiByteCache() = default;
            MultiByteCache( const MultiByteCache & ) = delete;
            MultiByteCache( MultiByteCache && other );

            MultiByteCache & operator = ( MultiByteCache && other );
        };
        mutable MultiByteCache m_MultiByteCache;
    };

# define YK_TXT( tag ) u##tag

}
