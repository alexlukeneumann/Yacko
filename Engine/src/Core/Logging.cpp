# include "Logging.h"

# if defined( YK_LOGGING )

# include <spdlog/sinks/stdout_color_sinks.h>
# include <spdlog/sinks/basic_file_sink.h>

# define YK_HAS_CONSOLE !defined( YK_DIST )

namespace Yk::Core
{
    std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;

    void Logger::Init()
    {
        std::vector<spdlog::sink_ptr> engineSinks = {
            std::make_shared<spdlog::sinks::basic_file_sink_mt>( "Engine.log", true ),
# if defined( YK_HAS_CONSOLE )
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
# endif
        };

        engineSinks[ 0 ]->set_pattern( "[%T] [%l] %n: %v" );
        engineSinks[ 0 ]->set_level( spdlog::level::trace );

# if defined( YK_HAS_CONSOLE )
        engineSinks[ 1 ]->set_pattern( "[%T] [%^%l%$] %n: %v" );
        engineSinks[ 1 ]->set_level( spdlog::level::info );
# endif

        s_EngineLogger = std::make_shared<spdlog::logger>( "Engine", engineSinks.begin(), engineSinks.end() );
        s_EngineLogger->set_level( spdlog::level::trace );
    }

    void Logger::Shutdown()
    {
        s_EngineLogger->flush();
        s_EngineLogger = nullptr;
    }
}

# endif
