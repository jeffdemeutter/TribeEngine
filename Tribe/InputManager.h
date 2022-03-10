#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"
#include "Commands.h"

enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY
};

class InputManager final : public Singleton<InputManager>
{
public:
	// first : Virtual-key code of the key, button, or stick movement.
	// second : Flags that indicate the keyboard state at the time of the input event.
	using KeyPair = std::pair<WORD, WORD>;


	static bool ProcessInput() { return GetInstance().ProcessInputImpl(); }
	static void AddInputMethod(WORD gamepadButton, WORD keyStroke, Command* pCommand) {
		GetInstance().AddInputMethodImpl(KeyPair{gamepadButton, keyStroke}, pCommand);
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;


	XINPUT_STATE m_ControllerState{};
	XINPUT_KEYSTROKE m_ControllerKeyStroke{};

	std::map<KeyPair, Command*> m_Commands;
	
	
	bool ProcessInputImpl();
	void AddInputMethodImpl(KeyPair keyPair, Command* pCommand);
	bool IsInputTrue(KeyPair inputCheck);
};


