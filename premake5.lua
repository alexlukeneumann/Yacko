#!lua

workspace "Yacko"
    startproject "Runtime"
    architecture "x64"
    staticruntime "off"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
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
            "YK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug*"
        defines
        {
            "YK_DEBUG"
        }
        optimize "off"
        symbols "on"

    filter "configurations:Release*"
        defines
        {
            "YK_RELEASE"
        }
        optimize "on"
        symbols "on"

    filter "configurations:Dist*"
        defines
        {
            "YK_DIST"
        }
        optimize "on"
        symbols "off"

include "Engine"
include "Runtime"
