# pragma once

# include "RTTI/TypeFlags.h"
# include "RTTI/NativeBindings.h"

namespace Yk::RTTI
{
    namespace Internal
    {
        class TypeDescriptorModifier;
    }

    class TypeDescriptor
    {
    public:
        TypeDescriptor() = default;

        inline const char * GetTypeName() const { return m_TypeName; }
        inline const char * GetAlias() const { return m_Alias; }
        inline uint64_t GetSize() const { return m_Size; }
        inline TypeFlags GetFlags() const { return m_Flags; }
        inline NativeBindings GetNativeBindings() const { return m_NativeBindings; }

        inline bool IsClass() const { return ( m_Flags & static_cast<TypeFlags>( TypeFlag::IsClass ) ) != 0; }
        inline bool IsArray() const { return ( m_Flags & static_cast<TypeFlags>( TypeFlag::IsArray ) ) != 0; }
        inline bool IsMap() const { return ( m_Flags & static_cast<TypeFlags>( TypeFlag::IsMap ) ) != 0; }
        inline bool IsPtr() const { return ( m_Flags & static_cast<TypeFlags>( TypeFlag::IsPtr ) ) != 0; }
        inline bool IsPolymorphic() const { return ( m_Flags & static_cast<TypeFlags>( TypeFlag::IsPolymorphic ) ) != 0; }

    private:
        friend class Internal::TypeDescriptorModifier;

    private:
        const char * m_TypeName{ nullptr };
        const char * m_Alias{ nullptr };
        uint64_t m_Size{ 0 };
        TypeFlags m_Flags{ 0 };
        NativeBindings m_NativeBindings;
    };
}
