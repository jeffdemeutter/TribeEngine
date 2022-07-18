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
#include "TurretComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	pFont;

	{ // main scene
		const auto pScene = m_GameContext.pSceneManager->AddScene("SinglePlayer");

		// tank
		const auto pTank = pScene->AddGameObject("PlayerTank");
		{ 
			const auto pTransform = pTank->AddComponent(new TransformComponent(pTank, RenderManager::GetWindowCenter()));
			const auto pRender = pTank->AddComponent(new RenderComponent(pTank, pTransform, "spritesheet.png"));
			const auto pPlayer = pTank->AddComponent(new PlayerTankComponent(pTank, pTransform, pRender));

			// tank inputs
			{
				InputAction right(new Command([pPlayer] { pPlayer->DoMovement(PlayerTankComponent::Movement::right); }));
					right.stroke = Stroke::held;
					right.keyboardKey = SDL_SCANCODE_D;
					right.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
				m_GameContext.pInput->AddInputAction(right);

				InputAction left(new Command([pPlayer] { pPlayer->DoMovement(PlayerTankComponent::Movement::left); }));
					left.stroke = Stroke::held;
					left.keyboardKey = SDL_SCANCODE_A;
					left.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
				m_GameContext.pInput->AddInputAction(left);

				InputAction up(new Command([pPlayer] { pPlayer->DoMovement(PlayerTankComponent::Movement::up); }));
					up.stroke = Stroke::held;
					up.keyboardKey = SDL_SCANCODE_W;
					up.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_UP;
				m_GameContext.pInput->AddInputAction(up);

				InputAction down(new Command([pPlayer] { pPlayer->DoMovement(PlayerTankComponent::Movement::down); }));
					down.stroke = Stroke::held;
					down.keyboardKey = SDL_SCANCODE_S;
					down.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
				m_GameContext.pInput->AddInputAction(down);
			}
		}

		// tank turret
		const auto pTankTurret = pTank->AddGameObject("Turret");
		{
			const auto pTransform = pTankTurret->AddComponent(new TransformComponent(pTankTurret, RenderManager::GetWindowCenter()));
			const auto pRender = pTankTurret->AddComponent(new RenderComponent(pTankTurret, pTransform, "spritesheet.png"));
			pRender->SetSrcRect(SDL_Rect{ 64,96,32,32 });
			pTankTurret->AddComponent(new TurretComponent(pTankTurret, m_Player, pTransform, pRender));
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
