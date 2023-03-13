# include "RTTI/Primitives.h"

# include "RTTI/TypeDescriptor.h"
# include "RTTI/TypeDescriptorModifier.h"

namespace Yk::RTTI
{
# define REFLECT_PRIMITIVE( type, alias )                                                   \
    template <>                                                                             \
    TypeDescriptor * GetPrimitiveTypeDescriptor<type>()                                     \
    {                                                                                       \
        static TypeDescriptor s_TypeDescriptor;                                             \
        Internal::TypeDescriptorModifier::SetTypeName( s_TypeDescriptor, #type );           \
        Internal::TypeDescriptorModifier::SetAlias( s_TypeDescriptor, alias );              \
        Internal::TypeDescriptorModifier::SetSize( s_TypeDescriptor, sizeof( type ) );      \
        Internal::TypeDescriptorModifier::SetNativeBindings( s_TypeDescriptor,              \
            NativeBindings(                                                                 \
                []() -> void * { return new type(); },                                      \
                []( void * obj ) { delete obj; }                                            \
            )                                                                               \
        );                                                                                  \
        return &s_TypeDescriptor;                                                           \
    }

    REFLECT_PRIMITIVE( uint8_t, "u8" );
    REFLECT_PRIMITIVE( uint16_t, "u16" );
    REFLECT_PRIMITIVE( uint32_t, "u32" );
    REFLECT_PRIMITIVE( uint64_t, "u64" );
    REFLECT_PRIMITIVE( int8_t, "s8" );
    REFLECT_PRIMITIVE( int16_t, "s16" );
    REFLECT_PRIMITIVE( int32_t, "s32" );
    REFLECT_PRIMITIVE( int64_t, "s64" );
    REFLECT_PRIMITIVE( float, "f32" );
    REFLECT_PRIMITIVE( double, "f64" );
    REFLECT_PRIMITIVE( bool, "bool" );
    REFLECT_PRIMITIVE( char, "char" );
}
