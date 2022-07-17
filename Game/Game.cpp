#include "GamePCH.h"
#include "Game.h"

#include "Font.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "InputManager.h"
#include "PlayerTankComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "RenderComponent.h"
#include "RenderManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "SpriteAnimationComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	pFont;

	{ // main scene
		const auto pScene = m_GameContext.pSceneManager->AddScene("SinglePlayer");

		// tank
		{ 
			const auto pTank = pScene->AddGameObject("PlayerTank");

			const auto pTransform = pTank->AddComponent(new TransformComponent(pTank, RenderManager::GetWindowCenter()));
			const auto pRender = pTank->AddComponent(new RenderComponent(pTank, pTransform, "spritesheet.png"));
			const auto pSAC = pTank->AddComponent(new SpriteAnimationComponent(pTank, pRender, 10));
			pTank->AddComponent(new PlayerTankComponent(pTank, pTransform, pSAC));
		}

		// fps object
		{
			auto pFps = pScene->AddGameObject("fps");
			
			const auto pTransform = pFps->AddComponent(new TransformComponent(pFps));
			const auto pRender = pFps->AddComponent(new RenderComponent(pFps, pTransform));
			const auto pText = pFps->AddComponent(new TextComponent(pFps, pRender, "", pFont, { 255,255,0,255 }));
			pFps->AddComponent(new FpsComponent(pFps, pText));
		}
	}
}