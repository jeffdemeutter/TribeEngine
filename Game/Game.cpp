#include "Game.h"

#include "GameObject.h"
#include "InputManager.h"
#include "iostream"
#include "Scene.h"
#include "SceneManager.h"
#include "TransformComponent.h"


void Game::LoadGame() const
{
	auto pScene = m_GameContext.pSceneManager->AddScene(std::make_shared<Scene>("MainScene"));

	auto pGo = pScene->AddGameObject("TestObject");
	pGo->AddComponent(new TransformComponent(pGo));

}