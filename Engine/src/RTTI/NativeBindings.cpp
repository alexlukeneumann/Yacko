# include "NativeBindings.h"

namespace Yk::RTTI
{
    NativeBindings::NativeBindings(
        CreateFunc createFunc,
        DestroyFunc destroyFunc
    )
        : m_CreateFunc{ createFunc }
        , m_DestroyFunc{ destroyFunc }
    {
    }
}
