#include "GamePCH.h"
#include "Game.h"

#include <CollisionComponent.h>
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
#include "TurretComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	pFont;

	{ // main scene
		const auto pScene = m_GameContext.pSceneManager->AddScene("SinglePlayer");


#pragma region Level
		const auto pBackground = pScene->AddGameObject("Background");
		{
			const auto pTrans = pBackground->AddComponent(new TransformComponent(pBackground, RenderManager::GetWindowCenter()));
			const auto pRender = pBackground->AddComponent(new RenderComponent(pBackground, pTrans, "background.png"));
			pRender->SetFullScreen(true);
		}

		const auto pLevel = pScene->AddGameObject("Level");
		{
			const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel));
			pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "level1.png"));
			const auto pLevelComponent = pLevel->AddComponent(new LevelComponent(pLevel, pTrans));

			pTrans->SetPosition(100, 100);

#pragma region Obstacles
			pLevelComponent->AddObstacle(
				{
					{0.f, 0.f},
					{0.f, 528.f},
					{64.f, 528.f},
					{64.f, 554.f},
					{0.f, 554.f},
					{0.f, 600.f},
					{600.f, 600.f},
					{600.f, 0.f},
					{560.f, 0.f},
					{560.f, 70.f},
					{536.f, 70.f},
					{536.f, 0.f}
				});

			pLevelComponent->AddObstacle(
				{
					{42.f, 44.f},
					{42.f, 92.f},
					{66.f, 92.f},
					{66.f, 44.f}
				});

			pLevelComponent->AddObstacle(
				{
					{106, 44},
					{106, 70},
					{170, 70},
					{170, 138},
					{194, 138},
					{194, 44},
				});

			pLevelComponent->AddObstacle(
				{
					{236, 44},
					{236, 70},
					{258, 70},
					{258, 44}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 44},
					{300, 70},
					{324, 70},
					{324, 44}
				});

			pLevelComponent->AddObstacle(
				{
					{366, 44},
					{366, 70},
					{496, 70},
					{496, 44}
				});

			pLevelComponent->AddObstacle(
				{
					{106, 112},
					{106, 138},
					{130, 138},
					{130, 112}
				});

			pLevelComponent->AddObstacle(
				{
					{236, 112},
					{236, 138},
					{258, 138},
					{258, 122}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 112},
					{300, 138},
					{366, 138},
					{366, 122}
				});

			pLevelComponent->AddObstacle(
				{
					{406, 112},
					{406, 138},
					{432, 138},
					{432, 122}
				});

			pLevelComponent->AddObstacle(
				{
					{536, 112},
					{536, 138},
					{560, 138},
					{560, 122}
				});

			pLevelComponent->AddObstacle(
				{
					{536, 182},
					{536, 276},
					{560, 276},
					{560, 182}
				});

			pLevelComponent->AddObstacle(
				{
					{472, 112},
					{472, 182},
					{406, 182},
					{406, 208},
					{496, 208},
					{496, 112}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 182},
					{300, 208},
					{366, 208},
					{366, 182}
				});

			pLevelComponent->AddObstacle(
				{
					{236, 182},
					{236, 208},
					{258, 208},
					{258, 182}
				});

			pLevelComponent->AddObstacle(
				{
					{170, 182},
					{170, 208},
					{194, 208},
					{194, 182}
				});

			pLevelComponent->AddObstacle(
				{
					{104, 182},
					{104, 208},
					{128, 208},
					{128, 182}
				});

			pLevelComponent->AddObstacle(
				{
					{40, 134},
					{40, 208},
					{64, 208},
					{64, 134}
				});

			pLevelComponent->AddObstacle(
				{
					{40, 250},
					{40, 348},
					{64, 348},
					{64, 250}
				});

			pLevelComponent->AddObstacle(
				{
					{104, 250},
					{104, 276},
					{128, 276},
					{128, 250}
				});

			pLevelComponent->AddObstacle(
				{
					{104, 322},
					{104, 348},
					{128, 348},
					{128, 322}
				});

			pLevelComponent->AddObstacle(
				{
					{170, 250},
					{170, 348},
					{194, 348},
					{194, 250}
				});

			pLevelComponent->AddObstacle(
				{
					{40, 392},
					{40, 486},
					{64, 486},
					{64, 418},
					{128, 418},
					{128, 392}
				});

			pLevelComponent->AddObstacle(
				{
					{106, 460},
					{106, 484},
					{128, 484},
					{128, 460}
				});

			pLevelComponent->AddObstacle(
				{
					{106, 530},
					{106, 554},
					{172, 554},
					{172, 530}
				});

			pLevelComponent->AddObstacle(
				{
					{170, 392},
					{170, 416},
					{192, 416},
					{192, 392}
				});

			pLevelComponent->AddObstacle(
				{
					{170, 392},
					{170, 486},
					{258, 486},
					{258, 392}
				});

			pLevelComponent->AddObstacle(
				{
					{212, 530},
					{212, 554},
					{258, 554},
					{258, 530}
				});

			pLevelComponent->AddObstacle(
				{
					{234, 390},
					{234, 418},
					{258, 418},
					{258, 390}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 390},
					{300, 418},
					{366, 418},
					{366, 390}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 460},
					{300, 486},
					{366, 486},
					{366, 460}
				});

			pLevelComponent->AddObstacle(
				{
					{300, 530},
					{300, 556},
					{366, 556},
					{366, 530}
				});

			pLevelComponent->AddObstacle(
				{
					{406, 250},
					{406, 346},
					{430, 346},
					{430, 250}
				});

			pLevelComponent->AddObstacle(
				{
					{472, 250},
					{472, 278},
					{496, 278},
					{496, 250}
				});

			pLevelComponent->AddObstacle(
				{
					{472, 320},
					{472, 390},
					{408, 390},
					{408, 416},
					{496, 416},
					{496, 320},
				});

			pLevelComponent->AddObstacle(
				{
					{536, 322},
					{536, 348},
					{560, 348},
					{560, 322}
				});

			pLevelComponent->AddObstacle(
				{
					{536, 392},
					{536, 418},
					{560, 418},
					{560, 392}
				});

			pLevelComponent->AddObstacle(
				{
					{536, 458},
					{536, 530},
					{406, 530},
					{406, 554},
					{560, 554},
					{560, 458}
				});

			pLevelComponent->AddObstacle(
				{
					{406, 462},
					{406, 488},
					{432, 488},
					{432, 462}
				});

			pLevelComponent->AddObstacle(
				{
					{472, 462},
					{472, 488},
					{496, 488},
					{496, 462}
				});

			pLevelComponent->AddObstacle(
				{
					{234, 252},
					{234, 346},
					{280, 346},
					{280, 322},
					{258, 322},
					{258, 276},
					{280, 276},
					{280, 252}
				});

			pLevelComponent->AddObstacle(
				{
					{320, 252},
					{320, 276},
					{344, 276},
					{344, 322},
					{320, 322},
					{320, 346},
					{366, 346},
					{366, 252}
				});
#pragma endregion
		}

		const auto pReset = pLevel->AddGameObject("Reset");
		{
			const auto pTrans = pReset->AddComponent(new TransformComponent(pReset));
			pReset->AddComponent(new CollisionComponent(pReset, pTrans, 86, 24));
			

			pTrans->SetPosition(300, 300);
		}

#pragma endregion

		// tank
		const auto pTank = pScene->AddGameObject("PlayerTank");
		{ 
			const auto pTransform = pTank->AddComponent(new TransformComponent(pTank, RenderManager::GetWindowCenter()));
			const auto pRender = pTank->AddComponent(new RenderComponent(pTank, pTransform, "spritesheet.png"));
			const auto pCollision = pTank->AddComponent(new CollisionComponent(pTank, pTransform, 14, 14));
			const auto pPlayer = pTank->AddComponent(new PlayerTankComponent(pTank, pTransform, pRender, pCollision));

			// collision
			pCollision->AddColliderCheck(
				pReset->GetComponent<CollisionComponent>(),
				new Command([this]
				{
					std::cout << "overlapping\n";
				})
			);

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
