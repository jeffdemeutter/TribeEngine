#pragma once

#include <iostream> // std::cout
#include <memory> // smart pointers
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "Structs.h"
#include "EventEnum.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#pragma warning (pop)

constexpr static float gPI = 3.141592f;