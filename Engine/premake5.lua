#!lua

project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "../bin/Engine/%{cfg.buildcfg}"
    objdir "../intermediates/Engine/%{cfg.buildcfg}"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "src"
    }
