# TribeEngine

## How to use
### Install VCPKG
This project uses VCPKG to manage the packages/libraries. For extra information about installing VCPKG, I recommend you to look into the official ["Getting started with VCPKG" page](https://vcpkg.io/en/getting-started.html). You can also take a look at my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md).

---

### Clone the repository
You want to clone this repository. We compile the project using MSBuild a.k.a. visual studio. Ofcourse this will not compile yet, because we have not installed the required packages. The following paragraph will explain how to install those packages.

---

### Packages to install 
The Tribe (Engine) utulizes different libraries/packages and as mentioned before, we manage those packages with vcpkg. I provide a single command that you have to run and it will install all the required packages. I keep the command(list) up-to-date, so you can compile the project in the future.

Packages:
- SDL2
- SDL2-ttf
- SDL2-image
- opengl
- glm
- ImGui
- ImGui-Docking

---

### Installing the packages
Navigate to the directory where you installed VCPKG. In my [Basic-VCPKG-guide](https://github.com/Tboske/Basic-VCPKG-guide/blob/main/README.md) I put this in `C:\vcpkg\` and I will use this as an example path. 

We need to run this with our cmd. Open a cmd and change the directory to the vcpkg directory (`cd C:\vcpkg\`). Once we are in this directory, we run the command below which will install all mandatory packages. The installation of these packages can take a while, enough time to treat yourself to a good cup of coffee.

`vcpkg install glm glm:x64-windows imgui imgui:x64-windows imgui[opengl2-binding] imgui[opengl2-binding]:x64-windows imgui[sdl2-binding] imgui[sdl2-binding]:x64-windows opengl opengl:x64-windows SDL2 SDL2:x64-windows SDL2-ttf SDL2-ttf:x64-windows SDL2-image SDL2-image:x64-windows sdl2-image[libjpeg-turbo] sdl2-image[libjpeg-turbo]:x64-windows imgui[docking-experimental] imgui[docking-experimental]:x64-windows --recurse`

This command will install all necessary packages in x86 and x64. You might also have noticed the --recurse flag which makes sure all bindings are properly installed. Once the installation is complete, you should be able to compile the project with MSBuild/Visual Studio. 

When that is done, you want to run `vcpkg integrate install` to ensure every packages is globaly available for MSBuild.
