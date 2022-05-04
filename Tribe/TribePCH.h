#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#pragma warning (pop)

#include <imgui.h>
#include <imgui_internal.h>

// this class should be available everywhere and doesn't change (a lot)
#include "ServiceLocator.h"

constexpr static int g_PixelScale = 3;

template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}
