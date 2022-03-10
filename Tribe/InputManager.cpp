#include "TribePCH.h"
#include "InputManager.h"
#include "RenderManager.h"

#include "imgui_impl_sdl.h"

bool InputManager::ProcessInputImpl()
{
	// updates the state of the controller
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(0, &m_ControllerState);

	ZeroMemory(&m_ControllerKeyStroke, sizeof(XINPUT_KEYSTROKE));
	XInputGetKeystroke(0, 0, &m_ControllerKeyStroke);

	// check if controller is connected
	if (result == ERROR_SUCCESS)
	{
		// process game input
		for (const auto& controllerCommand : m_Commands)
			if (IsInputTrue(controllerCommand.first))
				controllerCommand.second->Execute();


		// check to quit
		if (IsInputTrue({ static_cast<WORD>(VK_PAD_BACK), static_cast<WORD>(XINPUT_KEYSTROKE_KEYUP) }))
			return false;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		// check to quit
		if (e.type == SDL_QUIT)
			return false;
		
		// window resize
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				RenderManager::UpdateWindow(e.window.data1, e.window.data2);
				return true;
			}
		}

		// process game input

		// process event imgui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void InputManager::AddInputMethodImpl(ControllerPair keyPair, Command* pCommand)
{
	m_Commands[keyPair] = pCommand;
}

bool InputManager::IsInputTrue(ControllerPair inputCheck)
{
	if (m_ControllerKeyStroke.VirtualKey == inputCheck.first)
		return m_ControllerKeyStroke.Flags & inputCheck.second;

	return false;
}



