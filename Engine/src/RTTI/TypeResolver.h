# pragma once

# include "RTTI/TypeDescriptor.h"
# include "RTTI/Primitives.h"

namespace Yk::RTTI
{
    template <typename T>
    struct TypeResolver
    {
        static TypeDescriptor * Get()
        {
            return GetPrimitiveTypeDescriptor<T>();
        }
    };
}
