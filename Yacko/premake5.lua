#!lua

project "Yacko"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../bin/Yacko/%{cfg.buildcfg}"
    objdir "../intermediates/Yacko/%{cfg.buildcfg}"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "src"
    }

    dependson
    {
        "fmt"
    }

    links
    {
        "fmt"
    }
