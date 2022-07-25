workspace "SDLW"
    configurations {
        "Debug",
        "Release"
    }

project "SDLW"
    kind "StaticLib"
    language "C"

    targetdir ("bin/%{prj.name}/")
    objdir ("bin/%{prj.name}/obj/")

    pic "On"

    files {
        "include/SDLW/SDLW.h",

        "src/*.c",
        "src/*.h"
    }

    includedirs { "include/" }

    systemversion "latest"

    links { "sdl2" }

    filter "configurations:Debug"
        flags { "Symbols" }

    filter "configurations:Release"
        optimize "On"
