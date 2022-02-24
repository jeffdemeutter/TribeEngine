# TribeEngine

## How to use
### Installing VCPKG
This project uses VCPKG, for extra information about the VCPKG installation, I suggest you take a look at my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md).

---

### Packages to install 
The Tribe (engine) uses multiple libraries/packages and we manage those packages with vcpkg. 

I provide a .bat file to install these packages easily. I also provide a list of all the commands that are ran by the .bat file, in case you want to run these commands individually.

---

#### Usage .bat file
Copy the [TribeInstallPacks.bat](https://github.com/Tboske/TribeEngine/blob/master/TribeInstallPacks.bat) into your VCPKG install location. 

  If you followed my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md), I suggested installing VCPKG in `C:\vcpkg\`.

after having copied the .bat file, just run it and it should install everything. When the .bat file finishes the installation, you should be able to compile the project!

#### Commands list
Here are all the commands the .bat file runs and you can run them seperatly if you'd like.

- `vcpkg install glm`
- `vcpkg install glm:x64-windows`
- `vcpkg install imgui`
- `vcpkg install imgui:x64-windows`
- `vcpkg install imgui[opengl2-binding] --recurse`
- `vcpkg install imgui[opengl2-binding]:x64-windows --recurse`
- `vcpkg install imgui[sdl2-binding] --recurse`
- `vcpkg install imgui[sdl2-binding]:x64-windows --recurse`
- `vcpkg install opengl`
- `vcpkg install opengl:x64-windows`
- `vcpkg install SDL2`
- `vcpkg install SDL2:x64-windows`
- `vcpkg install SDL2-ttf`
- `vcpkg install SDL2-ttf:x64-windows`
- `vcpkg install SDL2-image`
- `vcpkg install SDL2-image:x64-windows`
- `vcpkg install sdl2-image[libjpeg-turbo] --recurse`
- `vcpkg install sdl2-image[libjpeg-turbo]:x64-windows --recurse`

