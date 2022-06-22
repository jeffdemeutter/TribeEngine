#pragma once

class InputManager;
class RenderManager;
class GameTime;

struct GameContext
{
	InputManager*	pInput		= nullptr;
	RenderManager*	pRenderer	= nullptr;
	GameTime*		pTime		= nullptr;
};
