#include "Game.h"

#include "GameObject.h"
#include "InputManager.h"
#include "iostream"
#include "Scene.h"
#include "SceneManager.h"
#include "TransformComponent.h"


void Game::LoadGame() const
{
	const auto pScene = m_GameContext.pSceneManager->AddScene("MainScene");

	const auto pGo = pScene->AddGameObject("TestObject");
	pGo->AddComponent(new TransformComponent(pGo));

	const auto pChild = pGo->AddGameObject("ChildObject");
	pChild->AddComponent(new TransformComponent(pChild));
}