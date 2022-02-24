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

If you followed my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md), I suggested installing VCPKG in `C:\vcpkg\`, so I will use this as example. If this is not applicable to you, use your VCPKG install directory.

After you have copied the .bat file, just run it and it should install everything. When the .bat file finishes the installation, you should be able to compile the project!

#### Commands list
If you prefer running all these commands yourself, you can! Below are all the commands listed up, it's as easy as just copy and pasting them. Make sure you run these commands in cmd within the directory of VCPKG.

- `vcpkg install glm glm:x64-windows imgui imgui:x64-windows imgui[opengl2-binding] imgui[opengl2-binding]:x64-windows imgui[sdl2-binding] imgui[sdl2-binding]:x64-windows opengl opengl:x64-windows SDL2 SDL2:x64-windows SDL2-ttf SDL2-ttf:x64-windows SDL2-image SDL2-image:x64-windows sdl2-image[libjpeg-turbo] sdl2-image[libjpeg-turbo]:x64-windows --recurse`

