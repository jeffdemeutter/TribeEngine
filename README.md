# TribeEngine

## How to use
### Installing VCPKG
This project uses VCPKG, for extra information about the VCPKG installation, I suggest you take a look at my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md).

---

### Packages to install 
The Tribe (engine) uses multiple libraries/packages and we manage those packages with vcpkg. I provide a single command that installs all the packages.

Packages:
- SDL2
- SDL2-ttf
- SDL2-image
- opengl
- glm
- ImGui

---

### Installing mandatory packages
If you followed my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md), I suggested installing VCPKG in `C:\vcpkg\`, so I will use this as example. If this is not applicable to you, use your VCPKG install directory.

Open the cmd in the `C:\vcpkg\` directory and then execute the command below. This will install all necessary packages in x86 and x64. 

`vcpkg install glm glm:x64-windows imgui imgui:x64-windows imgui[opengl2-binding] imgui[opengl2-binding]:x64-windows imgui[sdl2-binding] imgui[sdl2-binding]:x64-windows opengl opengl:x64-windows SDL2 SDL2:x64-windows SDL2-ttf SDL2-ttf:x64-windows SDL2-image SDL2-image:x64-windows sdl2-image[libjpeg-turbo] sdl2-image[libjpeg-turbo]:x64-windows --recurse`

After this you should be able to compile my project in visual studio.
