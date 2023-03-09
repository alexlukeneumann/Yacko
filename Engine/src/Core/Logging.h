# pragma once

# if defined( YK_LOGGING )

# include <spdlog/spdlog.h>

# include <memory>
# include <vector>

namespace Yk::Core::Internal
{
    class Logger
    {
    public:
        enum class Type : uint8_t
        {
            Engine,
            Editor,
            Client
        };

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
        static constexpr void LogMessage( Type type, Level level, Args &&... args );

    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static std::shared_ptr<spdlog::logger> s_EditorLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

    template <typename... Args>
    constexpr void Logger::LogMessage( Type type, Logger::Level level, Args &&... args )
    {
        std::shared_ptr<spdlog::logger> logger = nullptr;

        switch( type )
        {
        case Type::Engine:
            logger = s_EngineLogger;
            break;
        case Type::Editor:
            logger = s_EditorLogger;
            break;
        case Type::Client:
            logger = s_ClientLogger;
            break;
        }

        switch( level )
        {
        case Level::Trace:
            logger->trace( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Info:
            logger->info( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Warn:
            logger->warn( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Error:
            logger->error( fmt::format( std::forward<Args>( args )... ));
            break;
        case Level::Critical:
            logger->critical( fmt::format( std::forward<Args>( args )... ));
            break;
        }
    }
}

# define YK_LOGGING_INIT()          Yk::Core::Internal::Logger::Init();
# define YK_LOGGING_SHUTDOWN()      Yk::Core::Internal::Logger::Shutdown();

# define YK_ENGINE_TRACE( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Engine, Yk::Core::Internal::Logger::Level::Trace, __VA_ARGS__ );
# define YK_ENGINE_INFO( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Engine, Yk::Core::Internal::Logger::Level::Info, __VA_ARGS__ );
# define YK_ENGINE_WARN( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Engine, Yk::Core::Internal::Logger::Level::Warn, __VA_ARGS__ );
# define YK_ENGINE_ERROR( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Engine, Yk::Core::Internal::Logger::Level::Error, __VA_ARGS__ );
# define YK_ENGINE_CRITICAL( ... )  Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Engine, Yk::Core::Internal::Logger::Level::Critical, __VA_ARGS__ );

# define YK_EDITOR_TRACE( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Editor, Yk::Core::Internal::Logger::Level::Trace, __VA_ARGS__ );
# define YK_EDITOR_INFO( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Editor, Yk::Core::Internal::Logger::Level::Info, __VA_ARGS__ );
# define YK_EDITOR_WARN( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Editor, Yk::Core::Internal::Logger::Level::Warn, __VA_ARGS__ );
# define YK_EDITOR_ERROR( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Editor, Yk::Core::Internal::Logger::Level::Error, __VA_ARGS__ );
# define YK_EDITOR_CRITICAL( ... )  Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Editor, Yk::Core::Internal::Logger::Level::Critical, __VA_ARGS__ );

# define YK_CLIENT_TRACE( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Client, Yk::Core::Internal::Logger::Level::Trace, __VA_ARGS__ );
# define YK_CLIENT_INFO( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Client, Yk::Core::Internal::Logger::Level::Info, __VA_ARGS__ );
# define YK_CLIENT_WARN( ... )      Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Client, Yk::Core::Internal::Logger::Level::Warn, __VA_ARGS__ );
# define YK_CLIENT_ERROR( ... )     Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Client, Yk::Core::Internal::Logger::Level::Error, __VA_ARGS__ );
# define YK_CLIENT_CRITICAL( ... )  Yk::Core::Internal::Logger::LogMessage( Yk::Core::Internal::Logger::Type::Client, Yk::Core::Internal::Logger::Level::Critical, __VA_ARGS__ );

# else 

# define YK_LOGGING_INIT()
# define YK_LOGGING_SHUTDOWN()

# define YK_ENGINE_TRACE( ... )
# define YK_ENGINE_INFO( ... )
# define YK_ENGINE_WARN( ... )
# define YK_ENGINE_ERROR( ... )
# define YK_ENGINE_CRITICAL( ... )

# define YK_EDITOR_TRACE( ... )
# define YK_EDITOR_INFO( ... )
# define YK_EDITOR_WARN( ... )
# define YK_EDITOR_ERROR( ... )
# define YK_EDITOR_CRITICAL( ... )

# define YK_CLIENT_TRACE( ... )
# define YK_CLIENT_INFO( ... )
# define YK_CLIENT_WARN( ... )
# define YK_CLIENT_ERROR( ... )
# define YK_CLIENT_CRITICAL( ... )

# endif
