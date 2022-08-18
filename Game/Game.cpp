#include "GamePCH.h"
#include "Game.h"

#include <CollisionComponent.h>

#include "BulletConfigComponent.h"
#include "BulletManagerComponent.h"
#include "ButtonComponent.h"
#include "EnemyTank2Component.h"
#include "EnemyTankComponent.h"
#include "EnemyTankManager.h"
#include "EventManager.h"
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
#include "LivesComponent.h"
#include "MovementComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TurretComponent.h"

void Game::LoadGame() const
{
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	
#pragma region PersistantObjects
	// fps object
	auto pFps = new GameObject(nullptr, "fps");
	{
		const auto pTransform = pFps->AddComponent(new TransformComponent(pFps));
		const auto pRender = pFps->AddComponent(new RenderComponent(pFps, pTransform));
		const auto pText = pFps->AddComponent(new TextComponent(pFps, pRender, "", pFont, { 255,255,0,255 }));
		pFps->AddComponent(new FpsComponent(pFps, pText));
	}

	// High Score
	const auto pHighScore = new GameObject(nullptr, "HighScore");
	{
		const auto pTransform = pHighScore->AddComponent(new TransformComponent(pHighScore, 410, 25));
		const auto pRender = pHighScore->AddComponent(new RenderComponent(pHighScore, pTransform));
		const auto pText = pHighScore->AddComponent(new TextComponent(pHighScore, pRender, "0", pFont));
		pHighScore->AddComponent(new ScoreComponent(pHighScore, pText, "HighScores.txt"));
	}

	// lives
	const auto pLivesObject = new GameObject(nullptr, "Lives");
	{
		const auto pTransform = pLivesObject->AddComponent(new TransformComponent(pLivesObject, 320, 25));
		const auto pRender = pLivesObject->AddComponent(new RenderComponent(pLivesObject, pTransform));
		const auto pText = pLivesObject->AddComponent(new TextComponent(pLivesObject, pRender, " ", pFont, {255,0,0,255}));
		pLivesObject->AddComponent(new LivesComponent(pLivesObject, pText, 3));
	}
#pragma endregion

	// Main Menu
	{
		const auto& pMainMenu = m_GameContext.pSceneManager->AddScene("MainMenu");

		// singleplayer button
		{
			const auto pSP = pMainMenu->AddGameObject("SinglePlayer");
			const auto pTrans = pSP->AddComponent(new TransformComponent(pSP, 300, 200));
			const auto pRender = pSP->AddComponent(new RenderComponent(pSP, pTrans));
			pSP->AddComponent(new TextComponent(pSP, pRender, "SinglePlayer", pFont));

			const auto pCollision = pSP->AddComponent(new CollisionComponent(pSP, pTrans, 100, 40));
			const auto pButton = pSP->AddComponent(new ButtonComponent(pSP, pCollision, new Command([this]
			{
				m_GameContext.pSceneManager->ActivateScene("Scene1");
			})));

			InputAction input(new Command([pButton]
			{
				pButton->CheckIfClicked();
			}));
			input.stroke = Stroke::released;
			input.mouseButton = 0;
			m_GameContext.pInput->AddInputAction(input);
		}

		// coop button
		{
			const auto pCoop = pMainMenu->AddGameObject("Coop");
			const auto pTrans = pCoop->AddComponent(new TransformComponent(pCoop, 300, 250));
			const auto pRender = pCoop->AddComponent(new RenderComponent(pCoop, pTrans));
			pCoop->AddComponent(new TextComponent(pCoop, pRender, "Co-op", pFont));

			const auto pCollision = pCoop->AddComponent(new CollisionComponent(pCoop, pTrans, 100, 40));
			const auto pButton = pCoop->AddComponent(new ButtonComponent(pCoop, pCollision, new Command([this]
			{
				m_GameContext.pSceneManager->ActivateScene("Scene1");
			})));

			InputAction input(new Command([pButton]
			{
				pButton->CheckIfClicked();
			}));
			input.stroke = Stroke::released;
			input.mouseButton = 0;
			m_GameContext.pInput->AddInputAction(input);
		}
	}
	
	// scene
	{ 
		const auto pScene1 = m_GameContext.pSceneManager->AddScene("Scene1");
		{
			{
	#pragma region Level1
				const auto pBackground = pScene1->AddGameObject("Background");
				{
					const auto pTrans = pBackground->AddComponent(new TransformComponent(pBackground, RenderManager::GetWindowCenter()));
					const auto pRender = pBackground->AddComponent(new RenderComponent(pBackground, pTrans, "background.png"));
					pRender->SetFullScreen(true);
				}

				const auto pLevel = pScene1->AddGameObject("Level1");
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

				const auto pBulletManager = pScene1->AddGameObject("BulletManager");
				const auto pBulletManagerComp = pBulletManager->AddComponent(new BulletManagerComponent(pBulletManager, pLevel->GetComponent<LevelComponent>()));

				pScene1->AddGameObject(pFps);
				pScene1->AddGameObject(pHighScore);
				pScene1->AddGameObject(pLivesObject);

	#pragma region players
				// tank
				const auto pTank = pScene1->AddGameObject("Player1");
				{
					const auto pTransform = pTank->AddComponent(new TransformComponent(pTank, RenderManager::GetWindowCenter()));
					const auto pRender = pTank->AddComponent(new RenderComponent(pTank, pTransform, "spritesheet.png"));
					const auto pCollision = pTank->AddComponent(new CollisionComponent(pTank, pTransform, 25, 25));
					const auto pMovement = pTank->AddComponent(new MovementComponent(pTank, pTransform, pCollision));
					const auto pPlayer = pTank->AddComponent(new PlayerTankComponent(pTank, pRender, pMovement));
					pRender->SetSrcRect(SDL_Rect{ 00,64,32,32 });
					

					// collision
					pMovement->SetLevelComponent(pLevel->GetComponent<LevelComponent>());
					pCollision->AddColliderCheck(
						pReset->GetComponent<CollisionComponent>(),
						new Command([pTransform, pLevel]
					{
						pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
					})
					);
					pBulletManagerComp->AddCollision(pTank, new Command([pPlayer]
					{
						pPlayer->Kill();
					}));

					const auto respawnPlayer = [pTransform, pLevel](GameObject*, int)
					{
						pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
					};

					ServiceLocator::GetEventManager()->AddEventHandle(PlayerDied, respawnPlayer);
					ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, respawnPlayer);

					// tank inputs
					{
						InputAction right(new Command([pPlayer] { pPlayer->MoveRight(); }));
						right.stroke = Stroke::held;
						right.keyboardKey = SDL_SCANCODE_D;
						right.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
						m_GameContext.pInput->AddInputAction(right);

						InputAction left(new Command([pPlayer] { pPlayer->MoveLeft(); }));
						left.stroke = Stroke::held;
						left.keyboardKey = SDL_SCANCODE_A;
						left.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
						m_GameContext.pInput->AddInputAction(left);

						InputAction up(new Command([pPlayer] { pPlayer->MoveUp(); }));
						up.stroke = Stroke::held;
						up.keyboardKey = SDL_SCANCODE_W;
						up.ControllerButton = SDL_CONTROLLER_BUTTON_DPAD_UP;
						m_GameContext.pInput->AddInputAction(up);

						InputAction down(new Command([pPlayer] { pPlayer->MoveDown(); }));
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
					const auto pBulletConfig = pTankTurret->AddComponent(new BulletConfigComponent(pTankTurret));
					const auto pTurret = pTankTurret->AddComponent(new TurretComponent(pTankTurret, 0, pTransform, pRender, pBulletConfig));

					InputAction ia(new Command([pTurret] {pTurret->SpawnBullet(); }));
					ia.stroke = Stroke::released;
					ia.keyboardKey = SDL_SCANCODE_SPACE;
					ia.mouseButton = 0;
					m_GameContext.pInput->AddInputAction(ia);
				}
	#pragma endregion


#pragma region Enemies
				const auto pObject = pScene1->AddGameObject("enemyManager");
				const auto pEnemyManager = pObject->AddComponent(new EnemyTankManager(pObject, pTank, pLevel->GetComponent<LevelComponent>(), pBulletManagerComp));
				{
					pEnemyManager->AddEnemy(TankType::blueTank);

					pEnemyManager->AddEnemy(TankType::blueTank);

					pEnemyManager->AddEnemy(TankType::recognizer);
				}
#pragma endregion
			}
		}
		pScene1->Deactivate();


		const auto pGameOverScreen = m_GameContext.pSceneManager->AddScene("GameOver");
		{
			pGameOverScreen->AddSharedObject(pHighScore);

			int height = 40;
			for (int i = 0; i < 10; ++i)
			{
				const auto pHighScoreList = pGameOverScreen->AddGameObject("Highscore" + std::to_string(i));

				const auto pTrans = pHighScoreList->AddComponent(new TransformComponent(pHighScoreList, 350, float(200 + i * height)));
				const auto pRender = pHighScoreList->AddComponent(new RenderComponent(pHighScoreList, pTrans));
				const auto pText = pHighScoreList->AddComponent(new TextComponent(pHighScoreList, pRender, " ", pFont));

				const int score = pHighScore->GetComponent<ScoreComponent>()->GetScore(i);
				pText->SetText(std::to_string(i) + ": " + std::to_string(score));
			}
		}

		ServiceLocator::GetEventManager()->AddEventHandle(GameOver, [this, &pHighScore](GameObject*, int)
		{
			m_GameContext.pSceneManager->ActivateScene("GameOver");
			RenderManager::SetBackgroundColor({ 0,0,0,0 });
		});
	}

	m_GameContext.pSceneManager->ActivateScene("MainMenu");
}
