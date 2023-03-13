# include "TypeDescriptorModifier.h"

namespace Yk::RTTI::Internal
{
    void TypeDescriptorModifier::SetTypeName( TypeDescriptor & descriptor, const char * typeName )
    {
        descriptor.m_TypeName = typeName;
    }

    void TypeDescriptorModifier::SetAlias( TypeDescriptor & descriptor, const char * alias )
    {
        descriptor.m_Alias = alias;
    }

    void TypeDescriptorModifier::SetSize( TypeDescriptor & descriptor, uint64_t size )
    {
        descriptor.m_Size = size;
    }

    void TypeDescriptorModifier::SetFlags( TypeDescriptor & descriptor, TypeFlags flags )
    {
        descriptor.m_Flags = flags;
    }

    void TypeDescriptorModifier::SetNativeBindings( TypeDescriptor & descriptor, const NativeBindings & bindings )
    {
        descriptor.m_NativeBindings = bindings;
    }
}
