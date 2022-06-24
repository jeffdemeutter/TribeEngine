#include "TribePCH.h"
#include "InputManager.h"

#include "Structs.h"
#include "RenderManager.h"


bool InputAction::CheckController(const SDL_ControllerButtonEvent& cButton, Stroke strokeCheck)
{
	// check if its the correct controller
	if (cButton.which != ControllerID)
		return false;

	// if not the same key
	if (cButton.button != ControllerButton)
		return false;

	if (strokeCheck == Stroke::pressed)
	{
		// if key was already down
		if (keyDown)
			return false;

		// set key down for next frame
		keyDown = true;
		// checks if the input is a pressed input
		if (stroke != Stroke::pressed)
			return false;

		return true;
	}
	if (strokeCheck == Stroke::released)
	{
		// reset the button when its released
		keyDown = false;
		// check if the input is a released input
		if (stroke != Stroke::released)
			return false;

		return true;
	}

	return false;
}

bool InputAction::CheckKeyboard(const SDL_Scancode& scancode, Stroke strokeCheck)
{
	// if not the same key
	if (scancode != keyboardKey)
		return false;

	if (strokeCheck == Stroke::pressed)
	{
		// if key was already down
		if (keyDown)
			return false;
		// set key down for next frame
		keyDown = true;
		// checks if the input is a pressed input
		if (stroke != Stroke::pressed)
			return false;

		return true;
	}
	if (strokeCheck == Stroke::released)
	{
		// if not the same key
		if (scancode != keyboardKey)
			return false;
		// reset the button when its released
		keyDown = false;
		// check if the input is a released input
		if (stroke != Stroke::released)
			return false;

		return true;
	}

	return false;
}

InputManager::InputManager()
{
	SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
	
	for (int i = 0; i < m_MaxControllerCount; ++i)
	{
		if (!SDL_IsGameController(i))
			break;

		const auto& controller = SDL_GameControllerOpen(i);
		if (controller)
			m_pControllers.emplace_back(std::move(controller));
		else 
			std::cout << "Could not open gamecontroller " << i << ": " << SDL_GetError();
	}
}

InputManager::~InputManager()
{
	for (auto input : m_Commands)
		SafeDelete(input.pCommand);
}

bool InputManager::IsKeyboardKeyDown(SDL_Scancode scancode)
{
	// check continuous input
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	return keyState[scancode];
}

bool InputManager::IsControllerButtonDown(int controllerID, SDL_GameControllerButton controllerButton)
{

	return SDL_GameControllerGetButton(m_pControllers[controllerID], controllerButton);
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

#pragma region Keyboard Handler
		case SDL_KEYDOWN:
			for (InputAction& input : m_Commands)
				if (input.CheckKeyboard(e.key.keysym.scancode, Stroke::pressed))
					input.Execute();
			break;

		case SDL_KEYUP:
			for (InputAction& input : m_Commands)
				if (input.CheckKeyboard(e.key.keysym.scancode, Stroke::released))
					input.Execute();
			break;
#pragma endregion

#pragma region Controller
		// handles controller inputs
		case SDL_CONTROLLERBUTTONDOWN:
			for (InputAction& input : m_Commands)
				if (input.CheckController(e.cbutton, Stroke::pressed))
					input.Execute();
			break;

		case SDL_CONTROLLERBUTTONUP:
			for (InputAction& input : m_Commands)
				if (input.CheckController(e.cbutton, Stroke::released))
					input.Execute();
			break;
#pragma endregion
		}
		
	}

	// check continuous input
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	for (const InputAction& input : m_Commands)
	{
		if (!input.keyDown)
			continue;
		if (input.stroke != Stroke::held)
			continue;
		if (!keyState[input.keyboardKey])
			continue;
		if (!SDL_GameControllerGetButton(m_pControllers[input.ControllerID], input.ControllerButton))
			continue;

		input.Execute();
	}


	return true;
}

void InputManager::AddInputAction(const InputAction& input)
{
	if (input.ControllerID > m_MaxControllerCount)
		return;

	m_Commands.push_back(input);
}
