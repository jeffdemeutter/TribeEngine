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
	struct Input
	{
		WORD ControllerButton;
		WORD ControllerStroke;

		SDL_Scancode keyboardKey;
		KeyboardStroke keyboardStroke;
		// need a bool to check for key input down
		bool keyboardKeyDown = false;

		Command* pCommand = nullptr;
		void Execute() const { pCommand->Execute(); }
	};


	static bool ProcessInput() { return GetInstance().ProcessInputImpl(); }
	static void AddInputMethod(const Input& input) {
		GetInstance().AddInputMethodImpl(input);
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;


	XINPUT_STATE m_ControllerState{};
	XINPUT_KEYSTROKE m_ControllerKeyStroke{};
	
	std::vector<Input> m_Commands;
	
	
	bool ProcessInputImpl();
	void AddInputMethodImpl(const Input& input);
	bool IsInputTrue(const Input& input);
	bool HandleKeyboard();
};


