vcpkg install glm
vcpkg install glm --triplet=x64-windows
vcpkg install imgui
vcpkg install imgui --triplet=x64-windows
vcpkg install imgui[opengl2-binding] --recurse
vcpkg install imgui[opengl2-binding] --recurse --triplet=x64-windows
vcpkg install imgui[sdl2-binding] --recurse
vcpkg install imgui[sdl2-binding] --recurse --triplet=x64-windows
vcpkg install opengl
vcpkg install opengl --triplet=x64-windows
vcpkg install SDL2
vcpkg install SDL2 --triplet=x64-windows
vcpkg install SDL2-ttf
vcpkg install SDL2-ttf --triplet=x64-windows
vcpkg install SDL2-image
vcpkg install SDL2-image --triplet=x64-windows
vcpkg install sdl2-image[libjpeg-turbo] --recurse
vcpkg install sdl2-image[libjpeg-turbo] --recurse --triplet=x64-windows
pause