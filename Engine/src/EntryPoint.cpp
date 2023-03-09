# include "Core/Logging.h"
# include "Core/UString.h"

# include <cstdint>
# include <vector>

namespace Yk
{
    uint32_t Main( const std::vector<Core::UString> & args )
    {
        YK_LOGGING_INIT();
        YK_LOGGING_SHUTDOWN();
        return 0;
    }
}

# if defined( YK_PLATFORM_WINDOWS )

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <shellapi.h>

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{
# if !defined( YK_DIST )
    YK_ENGINE_ASSERT( AllocConsole() );
# endif

    int32_t argc = 0;
    wchar_t ** argv = CommandLineToArgvW( GetCommandLineW(), &argc );

    std::vector<Yk::Core::UString> args;
    args.reserve( argc );

    for( auto i = 0; i < argc; ++i )
        args.emplace_back( argv[ i ] );

    const auto rc = Yk::Main( args );

# if !defined( YK_DIST )
    YK_ENGINE_ASSERT( FreeConsole() );
# endif

    return rc;
}

# else

# error Platform not supported!

# endif
