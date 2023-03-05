# include "Common.h"

# include "Core/Logging.h"

namespace Yk
{
    uint32_t Main( uint32_t argc, char ** argv )
    {
# if defined( YK_LOGGING )
        Core::Logger::Init();
# endif

# if defined( YK_LOGGING )
        Core::Logger::Shutdown();
# endif

        return 0;
    }
}

# if defined( YK_DIST )
# if defined( YK_PLATFORM_WINDOWS )

# include <Windows.h>

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{
    return (int)Yk::Main( __argc, __argv );
}

# else

# error Platform not supported!

# endif
# endif


# if defined( YK_DEBUG ) | defined( YK_RELEASE ) 
# if defined( YK_PLATFORM_WINDOWS )

int main( int argc, char ** argv )
{
    return (int)Yk::Main( argc, argv );
}

# else

# error Platform not supported!

# endif
# endif
