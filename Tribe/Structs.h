#pragma once

class InputManager;
class RenderManager;
class GameTime;

struct GameContext
{
	InputManager*	pInput		= nullptr;
	GameTime*		pTime		= nullptr;
};
