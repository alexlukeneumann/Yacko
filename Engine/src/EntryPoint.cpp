# include "Core/Logging.h"

# include <cstdint>

namespace Yk
{
    uint32_t Main( uint32_t argc, char ** argv )
    {
        YK_LOGGING_INIT();
        YK_LOGGING_SHUTDOWN();
        return 0;
    }
}

# if defined( YK_DIST )
# if defined( YK_PLATFORM_WINDOWS )

# include <Windows.h>

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{
    return static_cast<uint32_t>( Yk::Main( __argc, __argv ) );
}

# else

# error Platform not supported!

# endif
# endif


# if defined( YK_DEBUG ) | defined( YK_RELEASE ) 
# if defined( YK_PLATFORM_WINDOWS )

int main( int argc, char ** argv )
{
    return static_cast<uint32_t>( Yk::Main( argc, argv ) );
}

# else

# error Platform not supported!

# endif
# endif
