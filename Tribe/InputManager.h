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
	SDL_GameControllerButton ControllerButton = SDL_CONTROLLER_BUTTON_INVALID;

	SDL_Scancode keyboardKey = SDL_SCANCODE_UNKNOWN;
	Stroke stroke = Stroke::pressed;

	Uint32 mouseButton = 0;

private:
	Command* pCommand = nullptr;

	friend class InputManager;
	// need a bool to check for key input down
	bool keyDown = false;
};

class InputManager final
{
public:
	InputManager();
	~InputManager();

	static bool IsKeyboardKeyDown(SDL_Scancode scancode)
	{
		// check continuous input
		const Uint8* keyState = SDL_GetKeyboardState(nullptr);

		return keyState[scancode];
	}
	float GetJoystickAxis(int controllerID, SDL_GameControllerAxis axis) const;
	bool IsControllerButtonDown(int controllerID, SDL_GameControllerButton controllerButton) const
	{
		return SDL_GameControllerGetButton(m_pControllers[controllerID], controllerButton);
	}

	static glm::vec2 GetMousePosition();

	void AddInputAction(const InputAction& input);

private:
	static constexpr int m_MaxControllerCount = 4;
	int m_ControllerCount = 0;
	float m_DeadZone = 0.30f;
	std::vector<SDL_GameController*> m_pControllers;

	std::vector<InputAction> m_Commands;

	friend class Tribe;
	bool ProcessInput();


	bool CheckController(InputAction& input, const SDL_ControllerButtonEvent& cButton, Stroke strokeCheck);
	bool CheckKeyboard(InputAction& input, const SDL_Scancode& scancode, Stroke strokeCheck);
};


