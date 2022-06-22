#include "Game.h"
#include "InputManager.h"
#include "iostream"

void PrintStuff(const std::string& s)
{
	std::cout << s << '\n';
}

void Game::LoadGame() const
{
	InputManager::InputAction inputAction;
	inputAction.ControllerID = 0;
	inputAction.keyboardKey = SDL_SCANCODE_W;
	inputAction.keyboardStroke = InputManager::Stroke::released;
	inputAction.pCommand = new Command([] { PrintStuff("yay"); });

	m_GameContext.pInput->AddInputMethod(inputAction);
}