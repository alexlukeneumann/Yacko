#!lua

project "Runtime"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../bin/Runtime/%{cfg.buildcfg}"
    objdir "../intermediates/Runtime/%{cfg.buildcfg}"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "../Engine/src",
    }

    dependson
    {
        "Engine"
    }

    links
    {
        "Engine"
    }
