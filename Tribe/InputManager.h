#pragma once
#include "Command.h"

#include "SDL2/SDL.h"

struct GameContext;

class InputManager final
{
public:
	InputManager() = default;
	~InputManager();

	enum class Stroke
	{
		held,
		pressed,
		released
	};
	struct InputAction
	{
		// this only applies for controllers
		int ControllerID = 0;

		// use VK_PAD_
		//WORD ControllerButton;
		// use XINPUT_KEYSTROKE_
		//WORD ControllerStroke;

		SDL_Scancode keyboardKey;
		Stroke keyboardStroke = Stroke::pressed;
		// need a bool to check for key input down

		Command* pCommand = nullptr;

	private:
		friend class InputManager;
		bool keyboardKeyDown = false;
		void Execute() const {
			pCommand->Execute();
		}
	};


	bool ProcessInput(GameContext& gameContext);

	void AddInputMethod(const InputAction& input) {
		m_Commands.push_back(input);
	}
private:

	//XINPUT_STATE m_ControllerState{};
	//XINPUT_KEYSTROKE m_ControllerKeyStroke{};

	std::vector<InputAction> m_Commands;

	//bool CheckControllerInput(int controllerID, const InputAction& input);
	//bool HandleKeyboard();
	//bool HandleController();
};


