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
#include "PointsDisplayComponent.h"
#include "TurretComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);

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
			const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel, 100, 100));
			pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "level1.png"));
			const auto pLevelComponent = pLevel->AddComponent(new LevelComponent(pLevel, pTrans));
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
					{106.f, 44.f},
					{106.f, 70.f},
					{170.f, 70.f},
					{170.f, 138.f},
					{194.f, 138.f},
					{194.f, 44.f},
				});

			pLevelComponent->AddObstacle(
				{
					{236.f, 44.f},
					{236.f, 70.f},
					{258.f, 70.f},
					{258.f, 44.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 44.f},
					{300.f, 70.f},
					{324.f, 70.f},
					{324.f, 44.f}
				});

			pLevelComponent->AddObstacle(
				{
					{366.f, 44.f},
					{366.f, 70.f},
					{496.f, 70.f},
					{496.f, 44.f}
				});

			pLevelComponent->AddObstacle(
				{
					{106.f, 112.f},
					{106.f, 138.f},
					{130.f, 138.f},
					{130.f, 112.f}
				});

			pLevelComponent->AddObstacle(
				{
					{236.f, 112.f},
					{236.f, 138.f},
					{258.f, 138.f},
					{258.f, 122.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 112.f},
					{300.f, 138.f},
					{366.f, 138.f},
					{366.f, 122.f}
				});

			pLevelComponent->AddObstacle(
				{
					{406.f, 112.f},
					{406.f, 138.f},
					{432.f, 138.f},
					{432.f, 122.f}
				});

			pLevelComponent->AddObstacle(
				{
					{536.f, 112.f},
					{536.f, 138.f},
					{560.f, 138.f},
					{560.f, 122.f}
				});

			pLevelComponent->AddObstacle(
				{
					{536.f, 182.f},
					{536.f, 276.f},
					{560.f, 276.f},
					{560.f, 182.f}
				});

			pLevelComponent->AddObstacle(
				{
					{472.f, 112.f},
					{472.f, 182.f},
					{406.f, 182.f},
					{406.f, 208.f},
					{496.f, 208.f},
					{496.f, 112.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 182.f},
					{300.f, 208.f},
					{366.f, 208.f},
					{366.f, 182.f}
				});

			pLevelComponent->AddObstacle(
				{
					{236.f, 182.f},
					{236.f, 208.f},
					{258.f, 208.f},
					{258.f, 182.f}
				});

			pLevelComponent->AddObstacle(
				{
					{170.f, 182.f},
					{170.f, 208.f},
					{194.f, 208.f},
					{194.f, 182.f}
				});

			pLevelComponent->AddObstacle(
				{
					{104.f, 182.f},
					{104.f, 208.f},
					{128.f, 208.f},
					{128.f, 182.f}
				});

			pLevelComponent->AddObstacle(
				{
					{40.f, 134.f},
					{40.f, 208.f},
					{64.f, 208.f},
					{64.f, 134.f}
				});

			pLevelComponent->AddObstacle(
				{
					{40.f, 250.f},
					{40.f, 348.f},
					{64.f, 348.f},
					{64.f, 250.f}
				});

			pLevelComponent->AddObstacle(
				{
					{104.f, 250.f},
					{104.f, 276.f},
					{128.f, 276.f},
					{128.f, 250.f}
				});

			pLevelComponent->AddObstacle(
				{
					{104.f, 322.f},
					{104.f, 348.f},
					{128.f, 348.f},
					{128.f, 322.f}
				});

			pLevelComponent->AddObstacle(
				{
					{170.f, 250.f},
					{170.f, 348.f},
					{194.f, 348.f},
					{194.f, 250.f}
				});

			pLevelComponent->AddObstacle(
				{
					{40.f, 392.f},
					{40.f, 486.f},
					{64.f, 486.f},
					{64.f, 418.f},
					{128.f, 418.f},
					{128.f, 392.f}
				});

			pLevelComponent->AddObstacle(
				{
					{106.f, 460.f},
					{106.f, 484.f},
					{128.f, 484.f},
					{128.f, 460.f}
				});

			pLevelComponent->AddObstacle(
				{
					{106.f, 530.f},
					{106.f, 554.f},
					{172.f, 554.f},
					{172.f, 530.f}
				});

			pLevelComponent->AddObstacle(
				{
					{170.f, 392.f},
					{170.f, 416.f},
					{192.f, 416.f},
					{192.f, 392.f}
				});

			pLevelComponent->AddObstacle(
				{
					{170.f, 392.f},
					{170.f, 414.f},
					{192.f, 414.f},
					{192.f, 392.f}
				});

			pLevelComponent->AddObstacle(
				{
					{234.f, 392.f},
					{234.f, 414.f},
					{258.f, 414.f},
					{258.f, 392.f}
				});

			pLevelComponent->AddObstacle(
				{
					{170.f, 460.f},
					{170.f, 486.f},
					{258.f, 486.f},
					{258.f, 460.f}
				});

			pLevelComponent->AddObstacle(
				{
					{212.f, 530.f},
					{212.f, 554.f},
					{258.f, 554.f},
					{258.f, 530.f}
				});

			pLevelComponent->AddObstacle(
				{
					{234.f, 390.f},
					{234.f, 418.f},
					{258.f, 418.f},
					{258.f, 390.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 390.f},
					{300.f, 418.f},
					{366.f, 418.f},
					{366.f, 390.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 460.f},
					{300.f, 486.f},
					{366.f, 486.f},
					{366.f, 460.f}
				});

			pLevelComponent->AddObstacle(
				{
					{300.f, 530.f},
					{300.f, 556.f},
					{366.f, 556.f},
					{366.f, 530.f}
				});

			pLevelComponent->AddObstacle(
				{
					{406.f, 250.f},
					{406.f, 346.f},
					{430.f, 346.f},
					{430.f, 250.f}
				});

			pLevelComponent->AddObstacle(
				{
					{472.f, 250.f},
					{472.f, 278.f},
					{496.f, 278.f},
					{496.f, 250.f}
				});

			pLevelComponent->AddObstacle(
				{
					{472.f, 320.f},
					{472.f, 390.f},
					{408.f, 390.f},
					{408.f, 416.f},
					{496.f, 416.f},
					{496.f, 320.f},
				});

			pLevelComponent->AddObstacle(
				{
					{536.f, 322.f},
					{536.f, 348.f},
					{560.f, 348.f},
					{560.f, 322.f}
				});

			pLevelComponent->AddObstacle(
				{
					{536.f, 392.f},
					{536.f, 418.f},
					{560.f, 418.f},
					{560.f, 392.f}
				});

			pLevelComponent->AddObstacle(
				{
					{536.f, 458.f},
					{536.f, 530.f},
					{406.f, 530.f},
					{406.f, 554.f},
					{560.f, 554.f},
					{560.f, 458.f}
				});

			pLevelComponent->AddObstacle(
				{
					{406.f, 462.f},
					{406.f, 488.f},
					{432.f, 488.f},
					{432.f, 462.f}
				});

			pLevelComponent->AddObstacle(
				{
					{472.f, 462.f},
					{472.f, 488.f},
					{496.f, 488.f},
					{496.f, 462.f}
				});

			pLevelComponent->AddObstacle(
				{
					{234.f, 252.f},
					{234.f, 346.f},
					{280.f, 346.f},
					{280.f, 322.f},
					{258.f, 322.f},
					{258.f, 276.f},
					{280.f, 276.f},
					{280.f, 252.f}
				});

			pLevelComponent->AddObstacle(
				{
					{320.f, 252.f},
					{320.f, 276.f},
					{344.f, 276.f},
					{344.f, 322.f},
					{320.f, 322.f},
					{320.f, 346.f},
					{366.f, 346.f},
					{366.f, 252.f}
				});
#pragma endregion
		}

		const auto pReset = pLevel->AddGameObject("Reset");
		{
			const auto pTrans = pReset->AddComponent(new TransformComponent(pReset, 300, 300));
			pReset->AddComponent(new CollisionComponent(pReset, pTrans, 86, 24));
		}

#pragma endregion

		// tank
		const auto pTank = pScene->AddGameObject("PlayerTank");
		{ 
			const auto pTransform = pTank->AddComponent(new TransformComponent(pTank, RenderManager::GetWindowCenter()));
			const auto pRender = pTank->AddComponent(new RenderComponent(pTank, pTransform, "spritesheet.png"));
			const auto pCollision = pTank->AddComponent(new CollisionComponent(pTank, pTransform, 25, 25));
			const auto pPlayer = pTank->AddComponent(new PlayerTankComponent(pTank, pTransform, pRender, pCollision));

			// collision
			pCollision->AddColliderCheck(
				pReset->GetComponent<CollisionComponent>(),
				new Command([pTransform, pLevel]
				{
					pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
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

		// High Score
		const auto pHighScore = pScene->AddGameObject("HighScore");
		{
			const auto pTransform = pHighScore->AddComponent(new TransformComponent(pHighScore, 410, 25));
			const auto pRender = pHighScore->AddComponent(new RenderComponent(pHighScore, pTransform));
			const auto pText = pHighScore->AddComponent(new TextComponent(pHighScore, pRender, "0", pFont));
			pHighScore->AddComponent(new PointsDisplayComponent(pHighScore, pText));
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
