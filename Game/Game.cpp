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
#include "HighScoreComponent.h"
#include "Scene.h"

#include "InputManager.h"
#include "PlayerTankComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "RenderComponent.h"
#include "RenderManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include "LivesComponent.h"
#include "MovementComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "TurretComponent.h"

Game::~Game()
{
	SafeDelete(m_pFps);
	SafeDelete(m_pScore);
	SafeDelete(m_pLivesObject);
}

void Game::LoadGame()
{
	// sound effects
	ServiceLocator::GetSoundManager()->SetVolume(20);
	ServiceLocator::GetSoundManager()->LoadEffect(shot, "../Data/Sound/Shot.wav");
	ServiceLocator::GetSoundManager()->LoadEffect(GameEnd, "../Data/Sound/EndGame.wav");
	ServiceLocator::GetSoundManager()->LoadEffect(hit, "../Data/Sound/Hit.wav");

	InputAction reloadScene(new Command([]
	{
		ServiceLocator::GetEventManager()->Notify(nullptr, ReloadScene);
	}));
	reloadScene.stroke = Stroke::released;
	reloadScene.keyboardKey = SDL_SCANCODE_F1;
	m_GameContext.pInput->AddInputAction(reloadScene);

	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	
#pragma region PersistantObjects
	// fps object
	m_pFps = new GameObject(nullptr, "fps");
	{
		const auto pTransform = m_pFps->AddComponent(new TransformComponent(m_pFps));
		const auto pRender = m_pFps->AddComponent(new RenderComponent(m_pFps, pTransform));
		const auto pText = m_pFps->AddComponent(new TextComponent(m_pFps, pRender, "", pFont, { 255,255,0,255 }));
		m_pFps->AddComponent(new FpsComponent(m_pFps, pText));
	}

	// High Score
	m_pScore = new GameObject(nullptr, "HighScore");
	{
		const auto pTransform = m_pScore->AddComponent(new TransformComponent(m_pScore, 410, 25));
		const auto pRender = m_pScore->AddComponent(new RenderComponent(m_pScore, pTransform));
		const auto pText = m_pScore->AddComponent(new TextComponent(m_pScore, pRender, "0", pFont));
		m_pScore->AddComponent(new ScoreComponent(m_pScore, pText, "HighScores.txt"));
	}

	// lives
	m_pLivesObject = new GameObject(nullptr, "Lives");
	{
		const auto pTransform = m_pLivesObject->AddComponent(new TransformComponent(m_pLivesObject, 320, 25));
		const auto pRender = m_pLivesObject->AddComponent(new RenderComponent(m_pLivesObject, pTransform));
		const auto pText = m_pLivesObject->AddComponent(new TextComponent(m_pLivesObject, pRender, " ", pFont, {255,0,0,255}));
		m_pLivesObject->AddComponent(new LivesComponent(m_pLivesObject, pText, 3));
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
				m_GameContext.pSceneManager->ActivateScene("Scene3");
			})));

			InputAction input(new Command([pButton]
			{
				pButton->CheckIfClicked();
			}));
			input.stroke = Stroke::released;
			input.useMouse = true;
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
			input.useMouse = true;
			input.mouseButton = 0;
			m_GameContext.pInput->AddInputAction(input);
		}
	}

	// Level3
	{
		const auto pScene = m_GameContext.pSceneManager->AddScene("Scene3");
		{
#pragma region Level
			const auto pBackground = pScene->AddGameObject("Background");
			{
				const auto pTrans = pBackground->AddComponent(new TransformComponent(pBackground, RenderManager::GetWindowCenter()));
				const auto pRender = pBackground->AddComponent(new RenderComponent(pBackground, pTrans, "background.png"));
				pRender->SetFullScreen(true);
			}

			const auto pLevel = pScene->AddGameObject("Level1");
			{
				const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel, 100, 100));
				pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "level3.png"));
				pLevel->AddComponent(new LevelComponent(pLevel, pTrans, "../Data/Level3.bLevel"));
			}

			const auto pReset = pLevel->AddGameObject("Reset");
			{
				const auto pTrans = pReset->AddComponent(new TransformComponent(pReset, 300, 300));
				pReset->AddComponent(new CollisionComponent(pReset, pTrans, 86, 24));
			}
#pragma endregion

			const auto pBulletManager = pScene->AddGameObject("BulletManager");
			const auto pBulletManagerComp = pBulletManager->AddComponent(new BulletManagerComponent(pBulletManager, pLevel->GetComponent<LevelComponent>()));

			pScene->AddSharedObject(m_pFps);
			pScene->AddSharedObject(m_pScore);
			pScene->AddSharedObject(m_pLivesObject);

#pragma region Player
			// tank
			const auto pTank = pScene->AddGameObject("Player1");
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


				ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, [pTransform, pLevel](GameObject*, int)
				{
					pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
				});

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
				ia.useMouse = true;
				ia.mouseButton = 0;
				ia.ControllerID = 0;
				ia.ControllerButton = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
				m_GameContext.pInput->AddInputAction(ia);
			}

			const auto pObject = pScene->AddGameObject("enemyManager");
			const auto pEnemyManager = pObject->AddComponent(new EnemyTankManager(pObject, pTank, pLevel->GetComponent<LevelComponent>(), pBulletManagerComp));
			{
				pEnemyManager->AddEnemy(TankType::blueTank);
				pEnemyManager->AddEnemy(TankType::blueTank);
				pEnemyManager->AddEnemy(TankType::blueTank);
				pEnemyManager->AddEnemy(TankType::blueTank);
				pEnemyManager->AddEnemy(TankType::blueTank);

				pEnemyManager->AddEnemy(TankType::recognizer);
				pEnemyManager->AddEnemy(TankType::recognizer);
				pEnemyManager->AddEnemy(TankType::recognizer);
			}
#pragma endregion
		}
		pScene->Deactivate();
	}

	// Level2
	{
		const auto pScene = m_GameContext.pSceneManager->AddScene("Scene2");
		{
#pragma region Level
			const auto pBackground = pScene->AddGameObject("Background");
			{
				const auto pTrans = pBackground->AddComponent(new TransformComponent(pBackground, RenderManager::GetWindowCenter()));
				const auto pRender = pBackground->AddComponent(new RenderComponent(pBackground, pTrans, "background.png"));
				pRender->SetFullScreen(true);
			}

			const auto pLevel = pScene->AddGameObject("Level1");
			{
				const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel, 100, 100));
				pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "level2.png"));
				pLevel->AddComponent(new LevelComponent(pLevel, pTrans, "../Data/Level2.bLevel"));
			}

			const auto pReset = pLevel->AddGameObject("Reset");
			{
				const auto pTrans = pReset->AddComponent(new TransformComponent(pReset, 300, 300));
				pReset->AddComponent(new CollisionComponent(pReset, pTrans, 86, 24));
			}
#pragma endregion

			const auto pBulletManager = pScene->AddGameObject("BulletManager");
			const auto pBulletManagerComp = pBulletManager->AddComponent(new BulletManagerComponent(pBulletManager, pLevel->GetComponent<LevelComponent>()));

			pScene->AddSharedObject(m_pFps);
			pScene->AddSharedObject(m_pScore);
			pScene->AddSharedObject(m_pLivesObject);

#pragma region Player
			// tank
			const auto pTank = pScene->AddGameObject("Player1");
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


				ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, [pTransform, pLevel](GameObject*, int)
				{
					pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
				});

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
				ia.useMouse = true;
				ia.mouseButton = 0;
				ia.ControllerID = 0;
				ia.ControllerButton = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
				m_GameContext.pInput->AddInputAction(ia);
			}
#pragma endregion

#pragma region Enemies
			const auto pObject = pScene->AddGameObject("enemyManager");
			const auto pEnemyManager = pObject->AddComponent(new EnemyTankManager(pObject, pTank, pLevel->GetComponent<LevelComponent>(), pBulletManagerComp));
			{
				pEnemyManager->AddEnemy(TankType::blueTank);

				pEnemyManager->AddEnemy(TankType::blueTank);

				pEnemyManager->AddEnemy(TankType::blueTank);

				pEnemyManager->AddEnemy(TankType::recognizer);

				pEnemyManager->AddEnemy(TankType::recognizer);
			}
#pragma endregion
		}
		pScene->Deactivate();
	}

	// Level1
	{
		const auto pScene1 = m_GameContext.pSceneManager->AddScene("Scene1");
		{
			{
				const auto pBackground = pScene1->AddGameObject("Background");
				{
					const auto pTrans = pBackground->AddComponent(new TransformComponent(pBackground, RenderManager::GetWindowCenter()));
					const auto pRender = pBackground->AddComponent(new RenderComponent(pBackground, pTrans, "background.png"));
					pRender->SetFullScreen(true);
				}
#pragma region Level1

				const auto pLevel = pScene1->AddGameObject("Level1");
				{
					const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel, 100, 100));
					pLevel->AddComponent(new RenderComponent(pLevel, pTrans, "level1.png"));
					pLevel->AddComponent(new LevelComponent(pLevel, pTrans, "../Data/Level1.bLevel"));
				}

				const auto pReset = pLevel->AddGameObject("Reset");
				{
					const auto pTrans = pReset->AddComponent(new TransformComponent(pReset, 300, 300));
					pReset->AddComponent(new CollisionComponent(pReset, pTrans, 86, 24));
				}
#pragma endregion

				const auto pBulletManager = pScene1->AddGameObject("BulletManager");
				const auto pBulletManagerComp = pBulletManager->AddComponent(new BulletManagerComponent(pBulletManager, pLevel->GetComponent<LevelComponent>()));

				pScene1->AddSharedObject(m_pFps);
				pScene1->AddSharedObject(m_pScore);
				pScene1->AddSharedObject(m_pLivesObject);

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

					ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, [pTransform, pLevel](GameObject*, int)
					{
						pTransform->SetAbsolutePosition(pLevel->GetComponent<LevelComponent>()->GetRandomPosition());
					});

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
					ia.useMouse = true;
					ia.mouseButton = 0;
					ia.ControllerID = 0;
					ia.ControllerButton = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
					m_GameContext.pInput->AddInputAction(ia);
				}
#pragma endregion


#pragma region Enemies
				const auto pObject = pScene1->AddGameObject("enemyManager");
				const auto pEnemyManager = pObject->AddComponent(new EnemyTankManager(pObject, pTank, pLevel->GetComponent<LevelComponent>(), pBulletManagerComp));
				{
					pEnemyManager->AddEnemy(TankType::blueTank);
					pEnemyManager->AddEnemy(TankType::blueTank);
					pEnemyManager->AddEnemy(TankType::blueTank);

					pEnemyManager->AddEnemy(TankType::recognizer);
					pEnemyManager->AddEnemy(TankType::recognizer);
				}
#pragma endregion
			}
		}
		pScene1->Deactivate();
	}

	// game over screen
	{
		const auto pGameOverScreen = m_GameContext.pSceneManager->AddScene("GameOver");
		{
			pGameOverScreen->AddSharedObject(m_pScore);

			const auto pHighscores = pGameOverScreen->AddGameObject("HighScores");
			pHighscores->AddComponent(new HighScoreComponent(pHighscores, m_pScore->GetComponent<ScoreComponent>(), pFont));
		}
		pGameOverScreen->Deactivate();
	}

	ServiceLocator::GetEventManager()->AddEventHandle(GameOver, [this](GameObject*, int)
	{
		m_GameContext.pSceneManager->ActivateScene("GameOver");
		RenderManager::SetBackgroundColor({ 0,0,0,0 });
	});

	ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, [this](GameObject*, int)
	{
		const auto pSceneManager = m_GameContext.pSceneManager;
		const std::string& activeSceneName = pSceneManager->GetActiveScene()->GetName();
		if (activeSceneName == "Scene1")
			pSceneManager->ActivateScene("Scene2");
		else if (activeSceneName == "Scene2")
			pSceneManager->ActivateScene("Scene3");
		else if (activeSceneName == "Scene3")
			pSceneManager->ActivateScene("Scene1");
	});

	m_GameContext.pSceneManager->ActivateScene("MainMenu");  
}
