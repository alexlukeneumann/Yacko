# include "Core/UString.h"

# include <gtest/gtest.h>

namespace Yk::Core::Tests
{
    TEST( UStringTests, CanDefaultConstruct )
    {
        const UString str{};

        EXPECT_EQ( 0, str.Length() );
        EXPECT_EQ( 0, str.Capacity() );
        EXPECT_EQ( nullptr, str.CStr() );
        EXPECT_EQ( nullptr, str.ToMultiByte() );
    }

    TEST( UStringTests, CanConstructFromUTF16Str )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );
        const UString str{ tag };

        EXPECT_EQ( 13, str.Length() );
        EXPECT_EQ( 14, str.Capacity() );
        EXPECT_EQ( 0, memcmp( tag, str.CStr(), str.Length() * sizeof( char16_t )));
    }

    TEST( UStringTests, CanConstructFromMultiByteStr )
    {
        auto tag = "Hello World";
        const UString str{ tag };

        EXPECT_EQ( 11, str.Length() );
        EXPECT_EQ( 12, str.Capacity() );
        EXPECT_EQ( 0, memcmp( YK_TXT( "Hello World" ), str.CStr(), str.Length() * sizeof( char16_t )));
    }

    TEST( UStringTests, CanCopyConstruct )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );
        const UString str0{ tag };
        const UString str1{ str0 };

        EXPECT_EQ( str0.Length(), str1.Length() );
        EXPECT_EQ( str0.Capacity(), str1.Capacity() );
        EXPECT_EQ( 0, memcmp( str0.CStr(), str1.CStr(), str0.Length() * sizeof( char16_t )));
    }

    TEST( UStringTests, CanMoveConstruct )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );
        
        UString str0{ tag };
        str0.ToMultiByte();

        const UString str1{ std::move( str0 ) };

        EXPECT_EQ( 13, str1.Length() );
        EXPECT_EQ( 14, str1.Capacity() );
        EXPECT_EQ( 0, memcmp( tag, str1.CStr(), str1.Length() * sizeof( char16_t )));
        EXPECT_NE( nullptr, str1.ToMultiByte() );

        EXPECT_EQ( 0, str0.Length() );
        EXPECT_EQ( 0, str0.Capacity() );
        EXPECT_EQ( nullptr, str0.CStr() );
        EXPECT_EQ( nullptr, str0.ToMultiByte() );
    }

    TEST( UStringTests, CanCopyAssign )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );

        const UString str0{ tag };
        UString str1;
        str1 = str0;

        EXPECT_EQ( str0.Length(), str1.Length() );
        EXPECT_EQ( str0.Capacity(), str1.Capacity() );
        EXPECT_EQ( 0, memcmp( str0.CStr(), str1.CStr(), str0.Length() * sizeof( char16_t )));
    }

    TEST( UStringTests, CanMoveAssign )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );

        UString str0{ tag };
        UString str1;
        str1 = std::move( str0 );

        EXPECT_EQ( 13, str1.Length() );
        EXPECT_EQ( 14, str1.Capacity() );
        EXPECT_EQ( 0, memcmp( tag, str1.CStr(), str1.Length() * sizeof( char16_t )));
        EXPECT_NE( nullptr, str1.ToMultiByte() );

        EXPECT_EQ( 0, str0.Length() );
        EXPECT_EQ( 0, str0.Capacity() );
        EXPECT_EQ( nullptr, str0.CStr() );
        EXPECT_EQ( nullptr, str0.ToMultiByte() );
    }

    TEST( UStringTests, CanConvertToMultiByteString )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );
        const UString str{ tag };

        auto mbStr{ str.ToMultiByte() };
        EXPECT_EQ( 0, memcmp( "Hello ♥ World", mbStr, 15 ));
    }

    TEST( UStringTests, EmptyStringToMultiByteStringReturnsNullptr )
    {
        UString str{};
        EXPECT_EQ( nullptr, str.ToMultiByte() );
    }

    TEST( UStringTests, CanConvertToMultiByteStringAndBack )
    {
        auto tag = YK_TXT( "Hello \u2665 World" );
        const UString str0{ tag };

        auto mbTag{ str0.ToMultiByte() };
        const UString str1{ mbTag };

        EXPECT_EQ( 0, memcmp( tag, str1.CStr(), str1.Length() * sizeof( char16_t )));
        EXPECT_EQ( 13, str1.Length() );
        EXPECT_EQ( 14, str1.Capacity() );
    }

    TEST( UStringTests, EqualityOperators )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        auto tag1 = YK_TXT( "Hello World \u2665" );

        EXPECT_EQ( UString{}, UString{} );
        EXPECT_NE( UString{ tag0 }, UString{} );
        EXPECT_EQ( UString{ tag0 }, UString{ tag0 });
        EXPECT_NE( UString{ tag0 }, UString{ tag1 });
    }

    TEST( UStringTests, CanToLower )
    {
        auto tag0 = YK_TXT( "HeLlO \u2665 WorLd" );
        auto tag1 = YK_TXT( "hello \u2665 world" );
        auto tag2 = "hello ♥ world";

        UString str{ tag0 };
        str.ToLower();

        EXPECT_EQ( UString{ tag1 }, str );
        EXPECT_EQ( 0, memcmp( tag2, str.ToMultiByte(), 15 ));
    }

    TEST( UStringTests, CanToUpper )
    {
        auto tag0 = YK_TXT( "HeLlO \u2665 WorLd" );
        auto tag1 = YK_TXT( "HELLO \u2665 WORLD" );
        auto tag2 = "HELLO ♥ WORLD";

        UString str{ tag0 };
        str.ToUpper();

        EXPECT_EQ( UString{ tag1 }, str );
        EXPECT_EQ( 0, memcmp( tag2, str.ToMultiByte(), 15 ));
    }

    TEST( UStringTests, CanFind )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        auto tag1 = YK_TXT( "\u2665 Wor" );
        auto tag2 = YK_TXT( "Hello \u2665 World 123" );

        const UString str{ tag0 };
        EXPECT_EQ( 6, str.Find( tag1 ) );
        EXPECT_EQ( 6, str.Find( UString{ tag1 }));
        EXPECT_EQ( 6, str.Find( tag1, 0 ) );
        EXPECT_EQ( 6, str.Find( tag1, 6 ) );
        EXPECT_EQ( UString::NPOS, str.Find( tag1, 7 ) );
        EXPECT_EQ( UString::NPOS, str.Find( tag1, str.Length() ) );

        EXPECT_EQ( 0, str.Find( tag0 ));
        EXPECT_EQ( 0, str.Find( tag0, 0 ));
        EXPECT_EQ( UString::NPOS, str.Find( tag0, 1 ));
        EXPECT_EQ( UString::NPOS, str.Find( tag0, 5 ));

        EXPECT_EQ( UString::NPOS, str.Find( tag2 ));
        EXPECT_EQ( UString::NPOS, str.Find( tag2, str.Length() ));
    }

    TEST( UStringTests, CanFindLastOf )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        auto tag1 = YK_TXT( "\u2665 Wor" );
        auto tag2 = YK_TXT( "Hello \u2665 World 123" );

        const UString str{ tag0 };
        EXPECT_EQ( 6, str.FindLastOf( tag1 ));
        EXPECT_EQ( 6, str.FindLastOf( UString{ tag1 } ));
        EXPECT_EQ( 6, str.FindLastOf( tag1, str.Length() ) );
        EXPECT_EQ( 6, str.FindLastOf( tag1, 6 ) );
        EXPECT_EQ( UString::NPOS, str.FindLastOf( tag1, 5 ) );

        EXPECT_EQ( 0, str.FindLastOf( tag0 ));
        EXPECT_EQ( 0, str.FindLastOf( tag0, 0 ));
        EXPECT_EQ( 0, str.FindLastOf( tag0, 5 ));
        EXPECT_EQ( UString::NPOS, str.FindLastOf( tag0, str.Length() + 1 ));

        EXPECT_EQ( UString::NPOS, str.FindLastOf( tag2 ));
        EXPECT_EQ( UString::NPOS, str.FindLastOf( tag2, 0 ));
    }

    TEST( UStringTests, ContainsCorrectlyWorks )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        auto tag1 = YK_TXT( "\u2665 Wor" );

        const UString str{ tag0 };
        EXPECT_TRUE( str.Contains( tag1 ) );
        EXPECT_TRUE( str.Contains( UString{ tag1 }));
        EXPECT_TRUE( str.Contains( tag1, 0 ) );
        EXPECT_TRUE( str.Contains( tag1, 6 ) );
        EXPECT_FALSE( str.Contains( tag1, 7 ) );
        EXPECT_FALSE( str.Contains( tag1, str.Length() ) );
    }

    TEST( UStringTests, CanSubStr )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        const UString str{ tag0 };

        EXPECT_EQ( UString{ tag0 }, str.SubStr( 0 ));
        EXPECT_EQ( UString{ tag0 }, str.SubStr( 0, str.Length() ));
        EXPECT_EQ( UString{ tag0 }, str.SubStr( 0, str.Length() + 10 ));
        EXPECT_EQ( UString{ YK_TXT( "Hello" ) }, str.SubStr( 0, 5 ));
        EXPECT_EQ( UString{ YK_TXT( "\u2665 World" ) }, str.SubStr( 6 ));
        EXPECT_EQ( UString{}, str.SubStr( str.Length() ));
        EXPECT_EQ( UString{ YK_TXT( "d" )}, str.SubStr( str.Length() - 1 ));
    }

    TEST( UStringTests, CanAppend )
    {
        auto tag0 = YK_TXT( "Hello" );
        auto tag1 = YK_TXT( "Hello \u2665 World" );
        UString str{ tag0 };

        str.Append( YK_TXT( " \u2665 " ) );
        str += YK_TXT( "World" );

        EXPECT_EQ( UString{ tag1 }, str );
        EXPECT_EQ( 0, memcmp( "Hello ♥ World", str.ToMultiByte(), 15 ));
    }

    TEST( UStringTests, CanReserve )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        UString str{ tag0 };

        str.Reserve( 99 );
        EXPECT_EQ( 100, str.Capacity() );
        EXPECT_EQ( 13, str.Length() );
        EXPECT_EQ( UString{ tag0 }, str );

        str.Reserve( 5 );
        EXPECT_EQ( 100, str.Capacity() );
        EXPECT_EQ( 13, str.Length() );
        EXPECT_EQ( UString{ tag0 }, str );
    }

    TEST( UStringTests, CanIndexAccessCharacter )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        const UString str1{ tag0 };

        for( auto i = 0; i < 13; ++i )
            EXPECT_EQ( tag0[ i ], str1[ i ] );
    }

    TEST( UStringTests, CanResize )
    {
        auto tag0 = YK_TXT( "Hello \u2665 World" );
        UString str{ tag0 };

        str.Resize( 20, 't' );
        EXPECT_EQ( UString{ YK_TXT( "Hello \u2665 Worldttttttt" ) }, str );
        EXPECT_EQ( 0, memcmp( "Hello ♥ Worldttttttt", str.ToMultiByte(), 23 ) );

        str.Resize( 13 );
        EXPECT_EQ( UString{ tag0 }, str );

        str.Resize( 5 );
        EXPECT_EQ( UString{ YK_TXT( "Hello" ) }, str );

        str.Resize( 10 );
        EXPECT_EQ( 0, memcmp( YK_TXT( "Hello\0\0\0\0\0" ), str.CStr(), str.Length() ) );
        EXPECT_EQ( 0, memcmp( "Hello\0", str.ToMultiByte(), 6 ) );
    }
}
