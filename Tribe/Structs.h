#pragma once

class SceneManager;
class InputManager;
class GameTime;

struct GameContext
{
	InputManager*	pInput;
	GameTime*		pTime;
	SceneManager*	pSceneManager;
};
