#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Commands.h"


class InputManager final : public Singleton<InputManager>
{
public:
	~InputManager() override;

	enum class KeyboardStroke
	{
		hold,
		pressed,
		released
	};
	struct InputAction
	{
		// this only applies for controllers
		int ControllerID = 0;

		// use VK_PAD_
		WORD ControllerButton;
		// use XINPUT_KEYSTROKE_
		WORD ControllerStroke;

		SDL_Scancode keyboardKey;
		KeyboardStroke keyboardStroke = KeyboardStroke::pressed;
		// need a bool to check for key input down

		Command* pCommand = nullptr;
		void Execute() const { pCommand->Execute(); }

	private:
		friend class InputManager;
		bool keyboardKeyDown = false;
	};


	static bool ProcessInput();
	static void AddInputMethod(const InputAction& input) {
		Get().m_Commands.push_back(input);
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;
	
	XINPUT_STATE m_ControllerState{};
	XINPUT_KEYSTROKE m_ControllerKeyStroke{};
	
	std::vector<InputAction> m_Commands;

	bool CheckControllerInput(int controllerID, const InputAction& input);
	bool HandleKeyboard();
	bool HandleController();
};


