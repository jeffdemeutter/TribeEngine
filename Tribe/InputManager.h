#pragma once
#include "Command.h"

#include "SDL2/SDL.h"

struct GameContext;

enum class Stroke
{
	held,
	pressed,
	released
};

struct InputAction
{
	InputAction(Command* pCom) : pCommand(pCom) {}

	// this only applies for controllers
	int ControllerID = 0;
	SDL_GameControllerButton ControllerKey = SDL_CONTROLLER_BUTTON_INVALID;

	SDL_Scancode keyboardKey = SDL_SCANCODE_UNKNOWN;
	Stroke stroke = Stroke::pressed;


private:
	Command* pCommand = nullptr;

	friend class InputManager;
	// need a bool to check for key input down
	bool keyDown = false;
	bool CheckController(const SDL_ControllerButtonEvent& cButton, Stroke strokeCheck);
	bool CheckKeyboard(const SDL_Scancode& scancode, Stroke strokeCheck);

	void Execute() const {
		pCommand->Execute();
	}
};

class InputManager final
{
public:
	InputManager();
	~InputManager();


	bool ProcessInput(GameContext& gameContext);

	void AddInputAction(const InputAction& input);
private:
	static constexpr int m_MaxControllerCount = 4;

	std::vector<InputAction> m_Commands;

	std::vector<SDL_GameController*> m_pControllers;
};


