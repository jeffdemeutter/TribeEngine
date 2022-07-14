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

	{ // main scene
		const auto pScene = m_GameContext.pSceneManager->AddScene("MainScene");

		const auto pGo = pScene->AddGameObject("FpsObject");
		const auto pTrans = pGo->AddComponent(new TransformComponent(pGo));
		const auto pRender = pGo->AddComponent(new RenderComponent(pGo, pTrans));
		const auto pText = pGo->AddComponent(new TextComponent(pGo, pRender, " ", pFont));
		pGo->AddComponent(new FpsComponent(pGo, pText));

		auto inputAction1 = InputAction(new Command([pGo] { pGo->ToggleActive(); }));
		inputAction1.stroke = Stroke::released;
		inputAction1.keyboardKey = SDL_SCANCODE_R;
		m_GameContext.pInput->AddInputAction(inputAction1);
	}
}