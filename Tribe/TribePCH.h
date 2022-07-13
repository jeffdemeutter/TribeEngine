#pragma once

#include <iostream> // std::cout
#include <memory> // smart pointers
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#pragma warning (pop)

#include "Structs.h"

template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}