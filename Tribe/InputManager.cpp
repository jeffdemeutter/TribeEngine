#include "TribePCH.h"
#include "InputManager.h"
#include "RenderManager.h"

#include "imgui_impl_sdl.h"

InputManager::~InputManager()
{
	for (auto input : m_Commands)
		SafeDelete(input.pCommand);
	
}

bool InputManager::ProcessInput()
{
	if (!Get().HandleController())
		return false;

	return Get().HandleKeyboard();
}

bool InputManager::CheckControllerInput(int controllerID, const InputAction& input)
{
	if (controllerID != input.ControllerID)
		return false;

	if (m_ControllerKeyStroke.VirtualKey != input.ControllerButton)
		return false;

	return m_ControllerKeyStroke.Flags & input.ControllerStroke;
}

bool InputManager::HandleKeyboard()
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
				if (input.keyboardStroke != KeyboardStroke::pressed)
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
				if (input.keyboardStroke != KeyboardStroke::released)
					continue;

				input.Execute();
			}
			break;
		}

		// process event imgui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	// check continuous input
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	for (const InputAction& input : m_Commands)
	{
		if (!input.keyboardKeyDown)
			continue;
		if (input.keyboardStroke != KeyboardStroke::hold)
			continue;
		if (!keyState[input.keyboardKey])
			continue;

		input.Execute();
	}

	return true;
}

bool InputManager::HandleController()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_ControllerKeyStroke, sizeof(XINPUT_KEYSTROKE));
		XInputGetKeystroke(i, 0, &m_ControllerKeyStroke);

		if (XInputGetState(i, &m_ControllerState) != ERROR_SUCCESS)
			continue;


		// process game input
		for (const auto& controllerCommand : m_Commands)
			if (CheckControllerInput(i, controllerCommand))
				controllerCommand.Execute();
	}

	//// updates the state of the controller
	//ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
	//DWORD result = XInputGetState(0, &m_ControllerState);

	//ZeroMemory(&m_ControllerKeyStroke, sizeof(XINPUT_KEYSTROKE));
	//XInputGetKeystroke(0, 0, &m_ControllerKeyStroke);

	//// check if controller is connected
	//if (result != ERROR_SUCCESS)
	//	return true;		

	return true;
}



