# include "Logging.h"

# if defined( YK_LOGGING )

# include <spdlog/sinks/stdout_color_sinks.h>
# include <spdlog/sinks/basic_file_sink.h>

# define YK_HAS_CONSOLE !defined( YK_DIST )

namespace Yk::Core::Internal
{
    std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_EditorLogger;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

    void Logger::Init()
    {
        // Engine Logger

        std::vector<spdlog::sink_ptr> engineSinks = {
            std::make_shared<spdlog::sinks::basic_file_sink_mt>( "Engine.log", true ),
# if defined( YK_HAS_CONSOLE )
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
# endif
        };

        engineSinks[ 0 ]->set_pattern( "[%T] [%t] [%l] %n: %v" );
        engineSinks[ 0 ]->set_level( spdlog::level::trace );

# if defined( YK_HAS_CONSOLE )
        engineSinks[ 1 ]->set_pattern( "[%T] [%t] [%^%l%$] %n: %v" );
        engineSinks[ 1 ]->set_level( spdlog::level::info );
# endif

        s_EngineLogger = std::make_shared<spdlog::logger>( "ENGINE", engineSinks.begin(), engineSinks.end() );
        s_EngineLogger->set_level( spdlog::level::trace );

        // Editor Logger

        std::vector<spdlog::sink_ptr> editorSinks = {
            std::make_shared<spdlog::sinks::basic_file_sink_mt>( "Editor.log", true ),
# if defined( YK_HAS_CONSOLE )
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
# endif
        };

        editorSinks[ 0 ]->set_pattern( "[%T] [%t] [%l] %n: %v" );
        editorSinks[ 0 ]->set_level( spdlog::level::trace );

# if defined( YK_HAS_CONSOLE )
        editorSinks[ 1 ]->set_pattern( "[%T] [%t] [%^%l%$] %n: %v" );
        editorSinks[ 1 ]->set_level( spdlog::level::warn );
# endif

        s_EditorLogger = std::make_shared<spdlog::logger>( "EDITOR", editorSinks.begin(), editorSinks.end() );
        s_EditorLogger->set_level( spdlog::level::trace );

        // Client Logger

        std::vector<spdlog::sink_ptr> clientSinks = {
            std::make_shared<spdlog::sinks::basic_file_sink_mt>( "Client.log", true ),
# if defined( YK_HAS_CONSOLE )
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
# endif
        };

        clientSinks[ 0 ]->set_pattern( "[%T] [%t] [%l] %n: %v" );
        clientSinks[ 0 ]->set_level( spdlog::level::trace );

# if defined( YK_HAS_CONSOLE )
        clientSinks[ 1 ]->set_pattern( "[%T] [%t] [%^%l%$] %n: %v" );
        clientSinks[ 1 ]->set_level( spdlog::level::info );
# endif

        s_ClientLogger = std::make_shared<spdlog::logger>( "CLIENT", clientSinks.begin(), clientSinks.end() );
        s_ClientLogger->set_level( spdlog::level::trace );
    }

    void Logger::Shutdown()
    {
        s_EngineLogger->flush();
        s_EditorLogger->flush();
        s_ClientLogger->flush();

        s_EngineLogger = nullptr;
        s_EditorLogger = nullptr;
        s_ClientLogger = nullptr;

        spdlog::drop_all();
    }
}

# endif
