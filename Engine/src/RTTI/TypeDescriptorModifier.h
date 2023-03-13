# pragma once

# include "RTTI/TypeDescriptor.h"

namespace Yk::RTTI::Internal
{
    class TypeDescriptorModifier
    {
    public:
        static void SetTypeName( TypeDescriptor & descriptor, const char * typeName );
        static void SetAlias( TypeDescriptor & descriptor, const char * alias );
        static void SetSize( TypeDescriptor & descriptor, uint64_t size );
        static void SetFlags( TypeDescriptor & descriptor, TypeFlags flags );
        static void SetNativeBindings( TypeDescriptor & descriptor, const NativeBindings & bindings );
    };
}
