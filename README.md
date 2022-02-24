# TribeEngine

## How to use
### Installing VCPKG
This project uses VCPKG, for extra information about the VCPKG installation, I suggest you take a look at my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md).


### Packages to install 
The Tribe (engine) uses multiple libraries/packages and we manage those packages with vcpkg. 

I provide a .bat file to install these packages easily. I also provide a list of all the commands that are ran by the .bat file, in case you want to run these commands individually.

#### usage .bat file
Copy the [TribeInstallPacks.bat](https://github.com/Tboske/TribeEngine/blob/master/TribeInstallPacks.bat) into your VCPKG install location. 

  If you followed my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md), I suggested installing VCPKG in `C:\vcpkg\`.

If you copied it into this directory, just run it and it should install everything. 

If this is done, you should be able to compile the project!

#### seperate commands
Here are all the commands the .bat file runs and you can run them seperatly if you'd like.

- `vcpkg install glm`
- `vcpkg install glm --triplet=x64-windows`
- `vcpkg install imgui`
- `vcpkg install imgui --triplet=x64-windows`
- `vcpkg install imgui[opengl2-binding] --recurse`
- `vcpkg install imgui[opengl2-binding] --recurse --triplet=x64-windows`
- `vcpkg install imgui[sdl2-binding] --recurse`
- `vcpkg install imgui[sdl2-binding] --recurse --triplet=x64-windows`
- `vcpkg install opengl`
- `vcpkg install opengl --triplet=x64-windows`
- `vcpkg install SDL2`
- `vcpkg install SDL2 --triplet=x64-windows`
- `vcpkg install SDL2-ttf`
- `vcpkg install SDL2-ttf --triplet=x64-windows`
- `vcpkg install SDL2-image`
- `vcpkg install SDL2-image --triplet=x64-windows`
- `vcpkg install sdl2-image[libjpeg-turbo] --recurse`
- `vcpkg install sdl2-image[libjpeg-turbo] --recurse --triplet=x64-windows`

After having installed all these packages, you should be able to compile the Tribe Engine
