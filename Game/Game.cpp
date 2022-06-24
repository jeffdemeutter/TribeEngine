#include "Game.h"
#include "InputManager.h"
#include "iostream"

void PrintStuff(const std::string& s)
{
	std::cout << s << '\n';
}

void Game::LoadGame() const
{
	InputAction inputAction {
		new Command([] { PrintStuff("yay"); })
	};
		inputAction.ControllerID = 0;
		inputAction.ControllerKey = SDL_CONTROLLER_BUTTON_A;
		inputAction.keyboardKey = SDL_SCANCODE_W;
		inputAction.stroke = Stroke::released;
	m_GameContext.pInput->AddInputAction(inputAction);


	InputAction ia{
		new Command([] { PrintStuff("noh"); })
	};
		ia.ControllerID = 0;
		ia.ControllerKey = SDL_CONTROLLER_BUTTON_B;
		ia.keyboardKey = SDL_SCANCODE_A;
		ia.stroke = Stroke::pressed;
	m_GameContext.pInput->AddInputAction(ia);

	InputAction ias{
	new Command([] { PrintStuff("wow"); })
	};
	ias.ControllerID = 0;
	ias.ControllerKey = SDL_CONTROLLER_BUTTON_X;
	ias.keyboardKey = SDL_SCANCODE_S;
	ias.stroke = Stroke::held;
	m_GameContext.pInput->AddInputAction(ias);
}