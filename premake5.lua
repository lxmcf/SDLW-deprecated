project "SDLW"
    kind "StaticLib"
    language "C"

    targetdir ("bin/%{prj.name}/")
    objdir ("bin/%{prj.name}/obj/")

    pic "On"

    files {
        "include/SDLW/SDLW.h",

        "src/SDLW_Window.c",
        "src/SDLW_Window.h"
    }

    includedirs {
        "include/"
    }

    defines { }

    systemversion "latest"

    links {
        "sdl2"
    }
