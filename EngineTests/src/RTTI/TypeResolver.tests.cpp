# include "RTTI/TypeResolver.h"

# include <gtest/gtest.h>

namespace Yk::RTTI::Tests
{
    TEST( TypeResolverTests, CanResolvePrimitives )
    {
        EXPECT_NE( nullptr, TypeResolver<uint8_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<uint16_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<uint32_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<uint64_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<int8_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<int16_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<int32_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<int64_t>::Get() );
        EXPECT_NE( nullptr, TypeResolver<float>::Get() );
        EXPECT_NE( nullptr, TypeResolver<double>::Get() );
        EXPECT_NE( nullptr, TypeResolver<bool>::Get() );
        EXPECT_NE( nullptr, TypeResolver<char>::Get() );
    }
}
