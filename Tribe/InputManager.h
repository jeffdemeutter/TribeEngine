#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"
#include "Commands.h"


class InputManager final : public Singleton<InputManager>
{
public:
	// first : Virtual-key code of the key, button, or stick movement.
	// second : Flags that indicate the keyboard state at the time of the input event.
	using ControllerPair = std::pair<WORD, WORD>;


	static bool ProcessInput() { return GetInstance().ProcessInputImpl(); }
	static void AddInputMethod(WORD gamepadButton, WORD keyStroke, Command* pCommand) {
		GetInstance().AddInputMethodImpl(ControllerPair{gamepadButton, keyStroke}, pCommand);
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;


	XINPUT_STATE m_ControllerState{};
	XINPUT_KEYSTROKE m_ControllerKeyStroke{};

	std::map<ControllerPair, Command*> m_Commands;
	
	
	bool ProcessInputImpl();
	void AddInputMethodImpl(ControllerPair keyPair, Command* pCommand);
	bool IsInputTrue(ControllerPair inputCheck);
};


