#!lua

workspace "Engine"
    startproject "Runtime"
    architecture "x64"
    staticruntime "off"

    configurations
    {
        "DebugVk",
        "ReleaseVk",
        "DistVk"
    }

    debugargs
    {
        "--workingDirectory=$(YACKO_WORKING_DIRECTORY)"
    }

    sysincludedirs
    {
        "imports/thirdparty/spdlog/include"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "YACKO_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug*"
        defines
        {
            "YACKO_DEBUG"
        }
        optimize "off"
        symbols "on"

    filter "configurations:Release*"
        defines
        {
            "YACKO_RELEASE"
        }
        optimize "on"
        symbols "on"

    filter "configurations:Dist*"
        defines
        {
            "YACKO_DIST"
        }
        optimize "on"
        symbols "off"

include "Yacko"
include "Runtime"
