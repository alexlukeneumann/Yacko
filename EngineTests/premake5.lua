#!lua

project "EngineTests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "../bin/EngineTests/%{cfg.buildcfg}"
    objdir "../intermediates/EngineTests/%{cfg.buildcfg}"

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

    sysincludedirs
    {
        "../imports/thirdparty/gtest/include"
    }
    
    syslibdirs
    {
        "../imports/thirdparty/gtest/lib"
    }

    dependson
    {
        "Engine"
    }

    links
    {
        "Engine"
    }

    filter "configurations:Debug"
        links
        {
            "gtestd",
            "gtest_maind"
        }

    filter "configurations:Release"
        links
        {
            "gtest",
            "gtest_main"
        }

    filter "configurations:Dist"
        kind "none"
    
