# pragma once

# if defined( YK_ASSERTS )

# include "Core/Logging.h"

# include <cstdint>

namespace Yk::Core::Internal
{
    template <typename... Args>
    constexpr void HandleEngineAssert(
        bool assert,
        const char * conditionStr,
        uint32_t lineNumber,
        const char * function,
        const char * file,
        Args &&... args
    )
    {
        if( !assert )
            return;

        const auto msg = sizeof...( args )
            ? fmt::format( "{}", std::forward<Args>( args )... )
            : "";

        YK_ENGINE_ERROR( "An assert occurred! \n Expression: '{}' \n Message: {} \n File: {} \n Function: {} \n Line: {}",
            conditionStr,
            msg,
            file,
            function,
            lineNumber
        );

        __debugbreak();
    }

    template <typename... Args>
    constexpr void HandleEngineVerify(
        bool verify,
        const char * conditionStr,
        uint32_t lineNumber,
        const char * function,
        const char * file,
        Args &&... args
    )
    {
        if( !verify )
            return;

        const auto msg = sizeof...( args )
            ? fmt::format( "{}", std::forward<Args>( args )... )
            : "";

        YK_ENGINE_CRITICAL( "An verify condition failed! \n Expression: '{}' \n Message: {} \n File: {} \n Function: {} \n Line: {}",
            conditionStr,
            msg,
            file,
            function,
            lineNumber
        );

        __debugbreak();
        std::terminate();
    }
}

/*
    YK_ENGINE_ASSERT( condition, ... )

    If the supplied condition evaluates to false, the message contained within __VA_ARGS__
    will be logged as a level of Yk::Core::Logger::Level::Error against the type
    Yk::Core::Logger::Type::Engine. Furthermore, the application will be temporarily
    paused on the assert to allow the developer to inspect the error. This is a non-fatal
    assert allowing the developer/user to ignore the assert.
*/
# define YK_ENGINE_ASSERT( condition, ... ) Yk::Core::Internal::HandleEngineAssert( !( condition ), #condition, __LINE__, __FUNCSIG__, __FILE__, __VA_ARGS__ );

/*
    YK_ENGINE_VERIFY( condition, ... )
    
    If the supplied condition evaluates to false, the message contained within __VA_ARGS__
    will be logged as a level of Yk::Core::Logger::Level::Critical against the type
    Yk::Core::Logger::Type::Engine. Furthermore, the application will be paused on the
    assert to allow the developer to inspect the error. This is a fatal assert and is
    non-skippable; the application will terminate.
*/
# define YK_ENGINE_VERIFY( condition, ... ) Yk::Core::Internal::HandleEngineVerify( !( condition ), #condition, __LINE__, __FUNCSIG__, __FILE__, __VA_ARGS__ );

# else

# define YK_ENGINE_ASSERT( condition, ... )
# define YK_ENGINE_VERIFY( condition, ... )

# endif 
