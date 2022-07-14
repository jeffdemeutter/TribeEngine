#include "Game.h"

#include "Font.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);


	const auto pScene = m_GameContext.pSceneManager->AddScene("MainScene");

	const auto pGo = pScene->AddGameObject("TestObject");
	const auto pTrans = pGo->AddComponent(new TransformComponent(pGo));
	const auto pRender = pGo->AddComponent(new RenderComponent(pGo, pTrans));
	const auto pText = pGo->AddComponent(new TextComponent(pGo, pRender, " ", pFont));
	pGo->AddComponent(new FpsComponent(pGo, pText));
	


	const auto pChild = pGo->AddGameObject("ChildObject");
	pChild->AddComponent(new TransformComponent(pChild));
}