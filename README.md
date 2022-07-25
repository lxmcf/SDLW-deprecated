<h1 align="center">SDLW</h1>

<p align="center">
    <
    <a href="#what-and-why">Description</a> |
    <a href="#dependencies">Dependencies</a> |
    <a href="#compiling">Compiling</a> |
    <a href="#roadmap">Roadmap</a>
    >
</p>

SDLW (SDL Wrapper) is a simple 'wrapper' for SDL2's window and renderer with an API inspired by GLFW3.

### What and why?
---

SDLW was inspired by the syntax of GLFW3, I found myself spending more time getting boiler plate SDL window and renderer creation than actual prototyping.

In every project I would start, I would either start copy-pasting a large chunk of code just to get basic events working or just rewriting the same code base with minor tweaks, I may as well build a simple wrapper I can include to expedite this step and here we are!

> _**Note:** I have only tested the current build using Fedora 36!_

### Dependencies
---

- `sdl2`

### Build Dependencies
---

- `gcc`
- `SDL2-devel`
- `meson`

### Compiling
---

SDLW can simply have the source code directly added to your current project, however it is recommended the static library is installed globally and linked!

```bash
# This is just a recommendation method
meson builddir --prefix=/usr
sudo meson install -C builddir

# Use these commands to just build the tests
meson builddir -Dbuild_examples=true
sudo meson compile -C builddir
```

### Roadmap
---

This roadmap outlines my current plans to implement features and will be updated as plans change

- __Version 1.0__
  - Basic window callback and creation

- __Version 2.0__
  - Initial renderer function wrapping
  - Add more window functions and callbacks
  - Update documentation

- __Version 2.1__
  - Add extra renderer functions (Primitive rendering, etc)
  - ~~Add compile time configurations~~

- __Version 3.0__
  - Custom texture wrapper
  - Texture loading via stb_image

- __Version 4.0__
  - Rework to allow multiple windows (May need total re-write of callback system)
