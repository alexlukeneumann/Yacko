# pragma once

# include <cstdint>

namespace Yk::RTTI
{
    class TypeDescriptor;

    template <typename T>
    TypeDescriptor * GetPrimitiveTypeDescriptor()
    {
        static_assert( false, "Unknown type T - is T reflected correctly?" );
        return nullptr;
    }

# define DECLARE_REFLECTED_PRIMITVE( type ) template <> TypeDescriptor* GetPrimitiveTypeDescriptor<type>();

    DECLARE_REFLECTED_PRIMITVE( uint8_t );
    DECLARE_REFLECTED_PRIMITVE( uint16_t );
    DECLARE_REFLECTED_PRIMITVE( uint32_t );
    DECLARE_REFLECTED_PRIMITVE( uint64_t );
    DECLARE_REFLECTED_PRIMITVE( int8_t );
    DECLARE_REFLECTED_PRIMITVE( int16_t );
    DECLARE_REFLECTED_PRIMITVE( int32_t );
    DECLARE_REFLECTED_PRIMITVE( int64_t );
    DECLARE_REFLECTED_PRIMITVE( float );
    DECLARE_REFLECTED_PRIMITVE( double );
    DECLARE_REFLECTED_PRIMITVE( bool );
    DECLARE_REFLECTED_PRIMITVE( char );
}
