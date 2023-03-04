# include "Common.h"

# include "fmt/format.h"

namespace Yacko
{
    uint32_t Main( uint32_t argc, char ** argv )
    {
        fmt::println( "Hello world!" );
        return 0;
    }
}

# if defined( YACKO_DIST )
# if defined( YACKO_PLATFORM_WINDOWS )

# include <Windows.h>

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{
    return (int)Yacko::Main( __argc, __argv );
}

# else

# error Platform not supported!

# endif
# endif


# if defined( YACKO_DEBUG ) | defined( YACKO_RELEASE ) 
# if defined( YACKO_PLATFORM_WINDOWS )

int main( int argc, char ** argv )
{
    return (int)Yacko::Main( argc, argv );
}

# else

# error Platform not supported!

# endif
# endif
