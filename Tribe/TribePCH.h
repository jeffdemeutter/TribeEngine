#pragma once

#include <iostream> // std::cout
#include <memory> // smart pointers
#include <vector>
#include <string>
#include <chrono>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#pragma warning (pop)



template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}