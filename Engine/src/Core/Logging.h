# pragma once

# if defined( YK_LOGGING )

# include <spdlog/spdlog.h>

# include <memory>
# include <vector>

namespace Yk::Core
{
    class Logger
    {
    public:
        enum class Level : uint8_t
        {
            Trace = 0,
            Info = 1,
            Warn = 2,
            Error = 3,
            Critical = 4
        };

        static void Init();
        static void Shutdown();

        template <typename... Args>
        static void LogMessage( Level level, Args &&... args );

    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
    };

    template <typename... Args>
    void Logger::LogMessage( Logger::Level level, Args &&... args )
    {
        switch( level )
        {
        case Level::Trace:
            s_EngineLogger->trace( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Info:
            s_EngineLogger->info( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Warn:
            s_EngineLogger->warn( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Error:
            s_EngineLogger->error( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Critical:
            s_EngineLogger->critical( fmt::format( std::forward<Args>( args )... ));
            break;
        }
    }
}

# define YK_ENGINE_TRACE( ... )     Yk::Core::Logger::LogMessage( Yk::Core::Logger::Level::Trace, __VA_ARGS__ );
# define YK_ENGINE_INFO( ... )      Yk::Core::Logger::LogMessage( Yk::Core::Logger::Level::Info, __VA_ARGS__ );
# define YK_ENGINE_WARN( ... )      Yk::Core::Logger::LogMessage( Yk::Core::Logger::Level::Warn, __VA_ARGS__ );
# define YK_ENGINE_ERROR( ... )     Yk::Core::Logger::LogMessage( Yk::Core::Logger::Level::Error, __VA_ARGS__ );
# define YK_ENGINE_CRITICAL( ... )  Yk::Core::Logger::LogMessage( Yk::Core::Logger::Level::Critical, __VA_ARGS__ );

# else 

# define YK_ENGINE_TRACE( ... )
# define YK_ENGINE_INFO( ... )
# define YK_ENGINE_WARN( ... )
# define YK_ENGINE_ERROR( ... )
# define YK_ENGINE_CRITICAL( ... )

# endif