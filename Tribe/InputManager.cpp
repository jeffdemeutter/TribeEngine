#include "TribePCH.h"
#include "InputManager.h"

#include "Structs.h"
#include "RenderManager.h"

InputManager::~InputManager()
{
	for (auto input : m_Commands)
		SafeDelete(input.pCommand);
}

bool InputManager::ProcessInput(GameContext& gameContext)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				gameContext.pRenderer->UpdateWindow(e.window.data1, e.window.data2);
				return true;
			}

		case SDL_KEYDOWN:
			for (InputAction& input : m_Commands)
			{
				// if not the same key
				if (e.key.keysym.scancode != input.keyboardKey)
					continue;
				// if key was already down
				if (input.keyboardKeyDown)
					continue;
				// set key down for next frame
				input.keyboardKeyDown = true;
				// checks if the input is a pressed input
				if (input.keyboardStroke != Stroke::pressed)
					continue;

				input.Execute();
			}
			break;

		case SDL_KEYUP:
			for (InputAction& input : m_Commands)
			{
				// if not the same key
				if (e.key.keysym.scancode != input.keyboardKey)
					continue;
				// reset the button when its released
				input.keyboardKeyDown = false;
				// check if the input is a released input
				if (input.keyboardStroke != Stroke::released)
					continue;

				input.Execute();
			}
			break;
		}
		
	}

	// check continuous input
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	for (const InputAction& input : m_Commands)
	{
		if (!input.keyboardKeyDown)
			continue;
		if (input.keyboardStroke != Stroke::held)
			continue;
		if (!keyState[input.keyboardKey])
			continue;

		input.Execute();
	}



	return true;
}
