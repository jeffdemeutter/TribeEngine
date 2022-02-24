vcpkg install glm
vcpkg install glm:x64-windows
vcpkg install imgui
vcpkg install imgui:x64-windows
vcpkg install imgui[opengl2-binding] --recurse
vcpkg install imgui[opengl2-binding]:x64-windows --recurse
vcpkg install imgui[sdl2-binding] --recurse
vcpkg install imgui[sdl2-binding]:x64-windows --recurse
vcpkg install opengl
vcpkg install opengl:x64-windows
vcpkg install SDL2
vcpkg install SDL2:x64-windows
vcpkg install SDL2-ttf
vcpkg install SDL2-ttf:x64-windows
vcpkg install SDL2-image
vcpkg install SDL2-image:x64-windows
vcpkg install sdl2-image[libjpeg-turbo] --recurse
vcpkg install sdl2-image[libjpeg-turbo]:x64-windows --recurse 
pause
