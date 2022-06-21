project ('SDLW', [ 'c' ], version: '1.0.0')

# Build variables
project_source = []
project_dependency = []
project_include = []

cc_arguments = []

# Compiler
cc = meson.get_compiler ('c')

add_project_arguments (cc_arguments, language: 'c')

project_source = files (
    'src/SDLW_Window.c'
)

project_include = include_directories (
    'src',
    'include'
)

project_dependency = [
    dependency ('sdl2')
]

project_library = static_library (
    meson.project_name (),
    project_source,

    dependencies: project_dependency,
    include_directories: project_include,

    install: true
)

install_headers ('include/SDLW/SDLW.h', subdir: meson.project_name ())

project_library_dependency = declare_dependency (
    link_with: project_library,
    version: meson.project_version (),

    dependencies: [
        project_dependency,
        cc.find_library ('m')
    ],

    include_directories: project_include
)

if get_option ('build_examples')
    subdir ('examples')
endif

pkgconfig = import ('pkgconfig', required: false)

if pkgconfig.found ()
    project_package = pkgconfig.generate (
        project_library,
        name: 'SDLW',
        requires: project_dependency,
        description: 'A simple wrapper for SDL2\'s window and renderer!',
        version: meson.project_version (),
        url: 'https://github.com/lxmcf/SDLW',
    )
else
    warning ('pkgconfig not found!')
endif
