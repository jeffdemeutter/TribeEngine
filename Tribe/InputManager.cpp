#include "TribePCH.h"
#include "InputManager.h"

#include "Structs.h"
#include "RenderManager.h"

InputManager::InputManager()
{
	m_pControllers.reserve(m_MaxControllerCount);

	SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < m_MaxControllerCount; ++i)
	{
		if (!SDL_IsGameController(i))
			break;

		auto controller = SDL_GameControllerOpen(i);
		if (!controller)
			std::cout << "Could not open gamecontroller " << i << ": " << SDL_GetError();
		
		m_pControllers.emplace_back(controller);
		++m_ControllerCount;
	}
}

InputManager::~InputManager()
{
	for (auto input : m_Commands)
		SafeDelete(input.pCommand);
}

float InputManager::GetJoystickAxis(int controllerID, SDL_GameControllerAxis axis)
{
	if (controllerID > m_ControllerCount)
		return 0;

	float normVal = float(SDL_GameControllerGetAxis(m_pControllers[controllerID], axis)) / SDL_MAX_SINT16;

	if (normVal < m_DeadZone && normVal > -m_DeadZone)
		normVal = 0;

	return normVal;
}

void InputManager::AddInputAction(const InputAction& input)
{
	if (input.ControllerID > m_MaxControllerCount)
		return;

	m_Commands.push_back(input);
}

bool InputManager::ProcessInput()
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
				RenderManager::UpdateWindow(e.window.data1, e.window.data2);
				return true;
			}

#pragma region Keyboard Handler
		case SDL_KEYDOWN:
			for (InputAction& input : m_Commands)
				if (CheckKeyboard(input, e.key.keysym.scancode, Stroke::pressed))
					input.pCommand->Execute();
			break;

		case SDL_KEYUP:
			for (InputAction& input : m_Commands)
				if (CheckKeyboard(input, e.key.keysym.scancode, Stroke::released))
					input.pCommand->Execute();
			break;
#pragma endregion

#pragma region Controller
			// handles controller inputs
		case SDL_CONTROLLERBUTTONDOWN:
			for (InputAction& input : m_Commands)
				if (CheckController(input, e.cbutton, Stroke::pressed))
					input.pCommand->Execute();
			break;

		case SDL_CONTROLLERBUTTONUP:
			for (InputAction& input : m_Commands)
				if (CheckController(input, e.cbutton, Stroke::released))
					input.pCommand->Execute();
			break;

		case SDL_CONTROLLERDEVICEADDED:
		{
			if (!SDL_IsGameController(e.cdevice.which))
				break;

			auto controller = SDL_GameControllerOpen(e.cdevice.which);
			if (!controller)
				std::cout << "Could not open gamecontroller " << e.cdevice.which << ": " << SDL_GetError();
			
			m_pControllers.emplace(m_pControllers.begin() + e.cdevice.which, controller);
			++m_ControllerCount;
			break;
		}

		case SDL_CONTROLLERDEVICEREMOVED:

			SDL_GameControllerClose(m_pControllers[e.cdevice.which]);

			m_pControllers.erase(m_pControllers.begin() + e.cdevice.which);
			--m_ControllerCount;
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

		input.pCommand->Execute();
	}

	//controller continuous checks
	for (const InputAction& input : m_Commands)
	{
		if (m_pControllers.empty())
			continue;
		if (input.ControllerID > m_ControllerCount)
			continue;
		if (input.stroke != Stroke::held)
			continue;
		if (!SDL_GameControllerGetButton(m_pControllers[input.ControllerID], input.ControllerButton))
			continue;

		input.pCommand->Execute();
	}

	return true;
}

bool InputManager::CheckController(InputAction& input, const SDL_ControllerButtonEvent& cButton, Stroke strokeCheck)
{
	// check if its the correct controller
	if (cButton.which != input.ControllerID)
		return false;

	// if not the same key
	if (cButton.button != input.ControllerButton)
		return false;

	if (strokeCheck == Stroke::pressed)
	{
		// if key was already down
		if (input.keyDown)
			return false;

		// set key down for next frame
		input.keyDown = true;
		// checks if the input is a pressed input
		if (input.stroke != Stroke::pressed)
			return false;

		return true;
	}
	if (strokeCheck == Stroke::released)
	{
		// reset the button when its released
		input.keyDown = false;
		// check if the input is a released input
		if (input.stroke != Stroke::released)
			return false;

		return true;
	}

	return false;
}

bool InputManager::CheckKeyboard(InputAction& input, const SDL_Scancode& scancode, Stroke strokeCheck)
{
	// if not the same key
	if (scancode != input.keyboardKey)
		return false;

	if (strokeCheck == Stroke::pressed)
	{
		// if key was already down
		if (input.keyDown)
			return false;
		// set key down for next frame
		input.keyDown = true;
		// checks if the input is a pressed input
		if (input.stroke != Stroke::pressed)
			return false;

		return true;
	}
	if (strokeCheck == Stroke::released)
	{
		// if not the same key
		if (scancode != input.keyboardKey)
			return false;
		// reset the button when its released
		input.keyDown = false;
		// check if the input is a released input
		if (input.stroke != Stroke::released)
			return false;

		return true;
	}

	return false;
}
