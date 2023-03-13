# pragma once

# include <cstdint>

namespace Yk::RTTI
{
    enum class TypeFlag : uint8_t
    {
        IsClass = 1 << 0,
        IsArray = 1 << 1,
        IsMap = 1 << 2,
        IsPtr = 1 << 3,
        IsPolymorphic = 1 << 4
    };

    using TypeFlags = uint8_t;
}
