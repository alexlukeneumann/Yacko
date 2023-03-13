# pragma once

namespace Yk::RTTI
{
    class NativeBindings
    {
    public:
        using CreateFunc = void * (*)();
        using DestroyFunc = void (*)( void * obj );

    public:
        NativeBindings() = default;
        NativeBindings(
            CreateFunc createFunc,
            DestroyFunc destroyFunc
        );

        inline CreateFunc GetCreateFunc() const { return m_CreateFunc; }
        inline DestroyFunc GetDestroyFunc() const { return m_DestroyFunc; }

    private:
        CreateFunc m_CreateFunc{ nullptr };
        DestroyFunc m_DestroyFunc{ nullptr };
    };
}
