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
#include "LevelComponent.h"
#include "TileComponent.h"
#include "TurretComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	pFont;

	{ // main scene
		const auto pScene = m_GameContext.pSceneManager->AddScene("SinglePlayer");


#pragma region Level
		const auto pLevel = pScene->AddGameObject("Level");
		{
			const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel, RenderManager::GetWindowCenter()));
			const auto pRender = pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "background.png"));
			const auto pLevelComponent = pLevel->AddComponent(new LevelComponent(pLevel, pTrans, pRender, "tilesheet.png", { 32,32 }, { 24,24 }));


			pLevelComponent->AddTile(0, 0, TileType::corner, -90);
			pLevelComponent->AddTile(0, 1, TileType::straight, 90);
			pLevelComponent->AddTile(0, 2, TileType::straight, 90);
			pLevelComponent->AddTile(0, 3, TileType::tPoint, -90);
			pLevelComponent->AddTile(0, 4, TileType::straight, 90);
			pLevelComponent->AddTile(0, 5, TileType::straight, 90);
			pLevelComponent->AddTile(0, 6, TileType::straight, 90);
			pLevelComponent->AddTile(0, 7, TileType::tPoint, -90);
			pLevelComponent->AddTile(0, 8, TileType::straight, 90);
			pLevelComponent->AddTile(0, 9, TileType::straight, 90);
			pLevelComponent->AddTile(0, 10, TileType::straight, 90);
			pLevelComponent->AddTile(0, 11, TileType::tPoint, -90);
			pLevelComponent->AddTile(0, 12, TileType::straight, 90);
			pLevelComponent->AddTile(0, 13, TileType::straight, 90);
			pLevelComponent->AddTile(0, 14, TileType::straight, 90);
			pLevelComponent->AddTile(0, 15, TileType::corner, 180);
			pLevelComponent->AddTile(0, 17, TileType::end, 180);


			pLevelComponent->AddTile(1, 0, TileType::straight);
			pLevelComponent->AddTile(1, 3, TileType::straight);
			pLevelComponent->AddTile(1, 7, TileType::straight);
			pLevelComponent->AddTile(1, 11, TileType::straight);
			pLevelComponent->AddTile(1, 15, TileType::straight);
			pLevelComponent->AddTile(1, 17, TileType::straight);


			pLevelComponent->AddTile(2, 0, TileType::tPoint);
			pLevelComponent->AddTile(2, 1, TileType::straight, 90);
			pLevelComponent->AddTile(2, 2, TileType::tPoint, -90);
			pLevelComponent->AddTile(2, 3, TileType::tPoint, 90);
			pLevelComponent->AddTile(2, 4, TileType::straight, 90);
			pLevelComponent->AddTile(2, 5, TileType::tPoint, -90);
			pLevelComponent->AddTile(2, 6, TileType::straight, 90);
			pLevelComponent->AddTile(2, 7, TileType::cross);
			pLevelComponent->AddTile(2, 8, TileType::straight, 90);
			pLevelComponent->AddTile(2, 9, TileType::tPoint, -90);
			pLevelComponent->AddTile(2, 10, TileType::straight, 90);
			pLevelComponent->AddTile(2, 11, TileType::tPoint, 180);
			pLevelComponent->AddTile(2, 13, TileType::corner, -90);
			pLevelComponent->AddTile(2, 14, TileType::straight, 90);
			pLevelComponent->AddTile(2, 15, TileType::cross);
			pLevelComponent->AddTile(2, 16, TileType::straight, 90);
			pLevelComponent->AddTile(2, 17, TileType::tPoint, 180);


			pLevelComponent->AddTile(3, 0, TileType::straight);
			pLevelComponent->AddTile(3, 2, TileType::straight);
			pLevelComponent->AddTile(3, 5, TileType::straight);
			pLevelComponent->AddTile(3, 7, TileType::straight);
			pLevelComponent->AddTile(3, 9, TileType::straight);
			pLevelComponent->AddTile(3, 11, TileType::straight);
			pLevelComponent->AddTile(3, 13, TileType::straight);
			pLevelComponent->AddTile(3, 15, TileType::straight);
			pLevelComponent->AddTile(3, 17, TileType::straight);


			pLevelComponent->AddTile(4, 0, TileType::straight);
			pLevelComponent->AddTile(4, 2, TileType::corner);
			pLevelComponent->AddTile(4, 3, TileType::straight, 90);
			pLevelComponent->AddTile(4, 4, TileType::straight, 90);
			pLevelComponent->AddTile(4, 5, TileType::cross);
			pLevelComponent->AddTile(4, 6, TileType::straight, 90);
			pLevelComponent->AddTile(4, 7, TileType::cross);
			pLevelComponent->AddTile(4, 8, TileType::straight, 90);
			pLevelComponent->AddTile(4, 9, TileType::tPoint, 90);
			pLevelComponent->AddTile(4, 10, TileType::straight, 90);
			pLevelComponent->AddTile(4, 11, TileType::cross);
			pLevelComponent->AddTile(4, 12, TileType::straight, 90);
			pLevelComponent->AddTile(4, 13, TileType::cross);
			pLevelComponent->AddTile(4, 14, TileType::straight, 90);
			pLevelComponent->AddTile(4, 15, TileType::tPoint, 180);
			pLevelComponent->AddTile(4, 17, TileType::straight);


			pLevelComponent->AddTile(5, 0, TileType::straight);
			pLevelComponent->AddTile(5, 5, TileType::straight);
			pLevelComponent->AddTile(5, 7, TileType::straight);
			pLevelComponent->AddTile(5, 11, TileType::straight);
			pLevelComponent->AddTile(5, 13, TileType::straight);
			pLevelComponent->AddTile(5, 15, TileType::tPoint);
			pLevelComponent->AddTile(5, 16, TileType::straight, 90);
			pLevelComponent->AddTile(5, 17, TileType::tPoint, 180);


			pLevelComponent->AddTile(6, 0, TileType::tPoint);
			pLevelComponent->AddTile(6, 1, TileType::straight, 90);
			pLevelComponent->AddTile(6, 2, TileType::tPoint, -90);
			pLevelComponent->AddTile(6, 3, TileType::straight, 90);
			pLevelComponent->AddTile(6, 4, TileType::straight, 90);
			pLevelComponent->AddTile(6, 5, TileType::cross, 90);
			pLevelComponent->AddTile(6, 6, TileType::straight, 90);
			pLevelComponent->AddTile(6, 7, TileType::cross, 90);
			pLevelComponent->AddTile(6, 8, TileType::straight, 90);
			pLevelComponent->AddTile(6, 9, TileType::straight, 90);
			pLevelComponent->AddTile(6, 10, TileType::straight, 90);
			pLevelComponent->AddTile(6, 11, TileType::cross);
			pLevelComponent->AddTile(6, 12, TileType::straight, 90);
			pLevelComponent->AddTile(6, 13, TileType::tPoint, 180);
			pLevelComponent->AddTile(6, 15, TileType::straight);
			pLevelComponent->AddTile(6, 17, TileType::straight);


			pLevelComponent->AddTile(7, 0, TileType::straight);
			pLevelComponent->AddTile(7, 2, TileType::straight);
			pLevelComponent->AddTile(7, 5, TileType::straight);
			pLevelComponent->AddTile(7, 7, TileType::straight);
			pLevelComponent->AddTile(7, 11, TileType::straight);
			pLevelComponent->AddTile(7, 13, TileType::straight);
			pLevelComponent->AddTile(7, 15, TileType::straight);
			pLevelComponent->AddTile(7, 17, TileType::straight);


			pLevelComponent->AddTile(8, 0, TileType::tPoint);
			pLevelComponent->AddTile(8, 1, TileType::straight, 90);
			pLevelComponent->AddTile(8, 2, TileType::cross);
			pLevelComponent->AddTile(8, 3, TileType::straight, 90);
			pLevelComponent->AddTile(8, 4, TileType::straight, 90);
			pLevelComponent->AddTile(8, 5, TileType::cross);
			pLevelComponent->AddTile(8, 6, TileType::straight, 90);
			pLevelComponent->AddTile(8, 7, TileType::cross);
			pLevelComponent->AddTile(8, 8, TileType::straight, 90);
			pLevelComponent->AddTile(8, 9, TileType::straight, 90);
			pLevelComponent->AddTile(8, 10, TileType::straight, 90);
			pLevelComponent->AddTile(8, 11, TileType::cross);
			pLevelComponent->AddTile(8, 12, TileType::straight, 90);
			pLevelComponent->AddTile(8, 13, TileType::cross);
			pLevelComponent->AddTile(8, 14, TileType::straight, 90);
			pLevelComponent->AddTile(8, 15, TileType::cross);
			pLevelComponent->AddTile(8, 16, TileType::straight, 90);
			pLevelComponent->AddTile(8, 17, TileType::tPoint, 180);



			pLevelComponent->AddTile(9, 0, TileType::straight);
			pLevelComponent->AddTile(9, 2, TileType::straight);
			pLevelComponent->AddTile(9, 5, TileType::straight);
			pLevelComponent->AddTile(9, 7, TileType::straight);
			pLevelComponent->AddTile(9, 11, TileType::straight);
			pLevelComponent->AddTile(9, 13, TileType::straight);
			pLevelComponent->AddTile(9, 15, TileType::straight);
			pLevelComponent->AddTile(9, 17, TileType::straight);


			pLevelComponent->AddTile(10, 0, TileType::tPoint);
			pLevelComponent->AddTile(10, 1, TileType::straight, 90);
			pLevelComponent->AddTile(10, 2, TileType::tPoint, 180);
			pLevelComponent->AddTile(10, 4, TileType::corner, -90);
			pLevelComponent->AddTile(10, 5, TileType::corner, 90);
			pLevelComponent->AddTile(10, 7, TileType::tPoint);
			pLevelComponent->AddTile(10, 8, TileType::straight, 90);
			pLevelComponent->AddTile(10, 9, TileType::straight, 90);
			pLevelComponent->AddTile(10, 10, TileType::straight, 90);
			pLevelComponent->AddTile(10, 11, TileType::cross);
			pLevelComponent->AddTile(10, 12, TileType::straight, 90);
			pLevelComponent->AddTile(10, 13, TileType::cross);
			pLevelComponent->AddTile(10, 14, TileType::straight, 90);
			pLevelComponent->AddTile(10, 15, TileType::cross);
			pLevelComponent->AddTile(10, 16, TileType::straight, 90);
			pLevelComponent->AddTile(10, 17, TileType::tPoint, 180);


			pLevelComponent->AddTile(11, 0, TileType::straight);
			pLevelComponent->AddTile(11, 2, TileType::straight);
			pLevelComponent->AddTile(11, 4, TileType::straight);
			pLevelComponent->AddTile(11, 7, TileType::straight);
			pLevelComponent->AddTile(11, 11, TileType::straight);
			pLevelComponent->AddTile(11, 13, TileType::straight);
			pLevelComponent->AddTile(11, 15, TileType::straight);
			pLevelComponent->AddTile(11, 17, TileType::straight);


			
			pLevelComponent->AddTile(12, 0, TileType::straight);
			pLevelComponent->AddTile(12, 2, TileType::straight);
			pLevelComponent->AddTile(12, 3, TileType::straight, 90);
			pLevelComponent->AddTile(12, 4, TileType::tPoint, 90);
			pLevelComponent->AddTile(12, 5, TileType::tPoint, -90);
			pLevelComponent->AddTile(12, 6, TileType::straight, 90);
			pLevelComponent->AddTile(12, 7, TileType::cross);
			pLevelComponent->AddTile(12, 8, TileType::straight, 90);
			pLevelComponent->AddTile(12, 9, TileType::corner, 180);
			pLevelComponent->AddTile(12, 11, TileType::straight);
			pLevelComponent->AddTile(12, 13, TileType::tPoint);
			pLevelComponent->AddTile(12, 14, TileType::straight, 90);
			pLevelComponent->AddTile(12, 15, TileType::tPoint, 180);
			pLevelComponent->AddTile(12, 17, TileType::straight);

			
			pLevelComponent->AddTile(13, 0, TileType::straight);
			pLevelComponent->AddTile(13, 2, TileType::straight);
			pLevelComponent->AddTile(13, 5, TileType::straight);
			pLevelComponent->AddTile(13, 7, TileType::straight);
			pLevelComponent->AddTile(13, 9, TileType::tPoint);
			pLevelComponent->AddTile(13, 10, TileType::straight, 90);
			pLevelComponent->AddTile(13, 11, TileType::tPoint, 90);
			pLevelComponent->AddTile(13, 12, TileType::tPoint, -90);
			pLevelComponent->AddTile(13, 13, TileType::corner, 90);
			pLevelComponent->AddTile(13, 15, TileType::straight);
			pLevelComponent->AddTile(13, 17, TileType::straight);


			pLevelComponent->AddTile(14, 0, TileType::straight);
			pLevelComponent->AddTile(14, 2, TileType::straight);
			pLevelComponent->AddTile(14, 5, TileType::straight);
			pLevelComponent->AddTile(14, 7, TileType::straight);
			pLevelComponent->AddTile(14, 9, TileType::straight);
			pLevelComponent->AddTile(14, 12, TileType::straight);
			pLevelComponent->AddTile(14, 15, TileType::straight);
			pLevelComponent->AddTile(14, 17, TileType::straight);


			pLevelComponent->AddTile(15, 0, TileType::corner);
			pLevelComponent->AddTile(15, 1, TileType::straight, 90);
			pLevelComponent->AddTile(15, 2, TileType::tPoint, 90);
			pLevelComponent->AddTile(15, 3, TileType::tPoint, -90);
			pLevelComponent->AddTile(15, 4, TileType::straight, 90);
			pLevelComponent->AddTile(15, 5, TileType::cross);
			pLevelComponent->AddTile(15, 6, TileType::straight, 90);
			pLevelComponent->AddTile(15, 7, TileType::cross);
			pLevelComponent->AddTile(15, 8, TileType::straight, 90);
			pLevelComponent->AddTile(15, 9, TileType::tPoint, 90);
			pLevelComponent->AddTile(15, 10, TileType::corner, 180);
			pLevelComponent->AddTile(15, 12, TileType::corner);
			pLevelComponent->AddTile(15, 13, TileType::tPoint, -90);
			pLevelComponent->AddTile(15, 14, TileType::straight, 90);
			pLevelComponent->AddTile(15, 15, TileType::corner, 90);
			pLevelComponent->AddTile(15, 17, TileType::straight);


			pLevelComponent->AddTile(16, 3, TileType::straight);
			pLevelComponent->AddTile(16, 5, TileType::straight);
			pLevelComponent->AddTile(16, 7, TileType::straight);
			pLevelComponent->AddTile(16, 10, TileType::straight);
			pLevelComponent->AddTile(16, 13, TileType::straight);
			pLevelComponent->AddTile(16, 17, TileType::straight);


			pLevelComponent->AddTile(17, 0, TileType::end, -90);
			pLevelComponent->AddTile(17, 1, TileType::straight, 90);
			pLevelComponent->AddTile(17, 2, TileType::straight, 90);
			pLevelComponent->AddTile(17, 3, TileType::tPoint, 90);
			pLevelComponent->AddTile(17, 4, TileType::straight, 90);
			pLevelComponent->AddTile(17, 5, TileType::tPoint, 90);
			pLevelComponent->AddTile(17, 6, TileType::straight, 90);
			pLevelComponent->AddTile(17, 7, TileType::tPoint, 90);
			pLevelComponent->AddTile(17, 8, TileType::straight, 90);
			pLevelComponent->AddTile(17, 9, TileType::straight, 90);
			pLevelComponent->AddTile(17, 10, TileType::tPoint, 90);
			pLevelComponent->AddTile(17, 11, TileType::straight, 90);
			pLevelComponent->AddTile(17, 12, TileType::straight, 90);
			pLevelComponent->AddTile(17, 13, TileType::tPoint, 90);
			pLevelComponent->AddTile(17, 14, TileType::straight, 90);
			pLevelComponent->AddTile(17, 15, TileType::straight, 90);
			pLevelComponent->AddTile(17, 16, TileType::straight, 90);
			pLevelComponent->AddTile(17, 17, TileType::corner, 90);
		}

#pragma endregion

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
			const auto pTurret = pTankTurret->AddComponent(new TurretComponent(pTankTurret, m_Player, pTransform, pRender));

			InputAction ia(new Command([pTurret] {pTurret->SpawnBullet(); }));
			ia.stroke = Stroke::released;
			ia.keyboardKey = SDL_SCANCODE_SPACE;
			ia.mouseButton = 0;
			m_GameContext.pInput->AddInputAction(ia);
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
