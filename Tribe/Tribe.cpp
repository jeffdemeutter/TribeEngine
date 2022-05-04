#include "TribePCH.h"
#include "Tribe.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"

#include "Components.h"
#include "ServiceLocator.h"

using namespace std;

/**
 * Code constructing the scene world starts here
 */
void Tribe::LoadGame() const
{
	// sounds
	ServiceLocator::GetSoundManager()->LoadEffect(playerHit, "../Data/Sound/LostLife.wav");

	// scene
	Scene* scene = SceneManager::CreateScene("Demo");
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);

	// background
	auto go = new GameObject("Background");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		go->AddComponent(new RenderComponent(go, pTransform, "background.jpg", true));
	}
	scene->Add(go);

	// fps object
	go = new GameObject("Fps object");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		const auto pText = go->AddComponent(new TextComponent(go, pRender, " ", pFont, { 255,255,0,255 }));
		go->AddComponent(new FpsComponent(go, pText));
	}
	scene->Add(go);

	auto* pPeterPepper = new GameObject("PeterPepper");
	{
		auto pPeter = pPeterPepper->AddComponent(new PeterPepperComponent(pPeterPepper));

		InputManager::InputAction input;
			input.keyboardKey = SDL_SCANCODE_D;
			input.pCommand = new Command([pPeter] { pPeter->DoDamage(); });
			input.ControllerButton = VK_PAD_X;
			input.ControllerStroke = XINPUT_KEYSTROKE_KEYUP;
		InputManager::AddInputMethod(input);
	}
	scene->Add(pPeterPepper);

	//auto* pPeterPepper2 = new GameObject("PeterPepper2");
	//{
	//	auto pPeter = pPeterPepper2->AddComponent(new PeterPepperComponent(pPeterPepper2));

	//	InputManager::InputAction input;
	//	input.ControllerID = 1;
	//	input.keyboardKey = SDL_SCANCODE_D;
	//	input.pCommand = new Command([pPeter] { pPeter->DoDamage(); });
	//	input.ControllerButton = VK_PAD_X;
	//	input.ControllerStroke = XINPUT_KEYSTROKE_KEYUP;
	//	InputManager::AddInputMethod(input);
	//}
	//scene->Add(pPeterPepper2);

	//auto* pDeadDisplay = new GameObject("DeadSign");
	//{
	//	const auto pTransform = pDeadDisplay->AddComponent(new TransformComponent(pDeadDisplay, 100,100));
	//	const auto pRender = pDeadDisplay->AddComponent(new RenderComponent(pDeadDisplay, pTransform));
	//	const auto pText = pDeadDisplay->AddComponent(new TextComponent(pDeadDisplay, pRender, "The player has died!", pFont, { 255,0,0,255 }, false));

	//	pDeadDisplay->AddComponent(new DeadSignComponent(pDeadDisplay, pText));
	//}
	//scene->Add(pDeadDisplay);

	//auto* pLivesDisplay = new GameObject("LivesDisplay");
	//{
	//	const auto pTransform = pLivesDisplay->AddComponent(new TransformComponent(pLivesDisplay, 100, 70));
	//	const auto pRender = pLivesDisplay->AddComponent(new RenderComponent(pLivesDisplay, pTransform));
	//	const auto pText = pLivesDisplay->AddComponent(new TextComponent(pLivesDisplay, pRender, "", pFont, { 255, 0, 0,255 }));

	//	pLivesDisplay->AddComponent(new RemainingLivesComponent(pLivesDisplay, pText));
	//}
	//scene->Add(pLivesDisplay);

	//pLivesDisplay = new GameObject("LivesDisplay2");
	//{
	//	const auto pTransform = pLivesDisplay->AddComponent(new TransformComponent(pLivesDisplay, 100, 250));
	//	const auto pRender = pLivesDisplay->AddComponent(new RenderComponent(pLivesDisplay, pTransform));
	//	const auto pText = pLivesDisplay->AddComponent(new TextComponent(pLivesDisplay, pRender, "", pFont, {0, 255, 0,255}));

	//	pLivesDisplay->AddComponent(new RemainingLivesComponent(pLivesDisplay, pText));
	//}
	//scene->Add(pLivesDisplay);

	//auto* pEnemyObject = new GameObject("Enemy");
	//{
	//	auto pEnemy = pEnemyObject->AddComponent(new EnemyComponent(pEnemyObject));

	//	InputManager::InputAction input;
	//	input.keyboardKey = SDL_SCANCODE_F;
	//	input.keyboardStroke = InputManager::KeyboardStroke::released;
	//	input.ControllerButton = VK_PAD_A;
	//	input.ControllerStroke = XINPUT_KEYSTROKE_KEYUP;
	//	input.pCommand = new Command([pEnemy] { pEnemy->KillEnemy(); });
	//	InputManager::AddInputMethod(input);

	//	InputManager::InputAction inputP2;
	//	inputP2.ControllerID = 1;
	//	inputP2.ControllerButton = VK_PAD_A;
	//	inputP2.ControllerStroke = XINPUT_KEYSTROKE_KEYUP;
	//	inputP2.pCommand = new Command([pEnemy] { pEnemy->KillEnemy(); });
	//	InputManager::AddInputMethod(inputP2);
	//}
	//scene->Add(pEnemyObject);

	//===========================================================================================
	// Level stuff
	//===========================================================================================

#pragma region Level
	const auto pLevel = new GameObject("Level");
	{
		LevelComponent* pLevelComp = pLevel->AddComponent(new LevelComponent(pLevel, 6, "tilesprites.png", {24, 16}));

		pLevelComp->AddTile({ 0,0 }, TileType::bottom	| TileType::top		| TileType::right);
		pLevelComp->AddTile({ 1,0 }, TileType::platform | TileType::right);
		pLevelComp->AddTile({ 2,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 3,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 4,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 5,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 6,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 7,0 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 8,0 }, TileType::left		| TileType::right	| TileType::bottom);

		pLevelComp->AddTile({ 0,1 }, TileType::bottom	| TileType::top		| TileType::right);
		pLevelComp->AddTile({ 1,1 }, TileType::platform | TileType::right);
		pLevelComp->AddTile({ 2,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 3,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 4,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 5,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 6,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 7,1 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 8,1 }, TileType::left		| TileType::right	| TileType::bottom);

		pLevelComp->AddTile({ 0,2 }, TileType::bottom	| TileType::top		| TileType::right);
		pLevelComp->AddTile({ 1,2 }, TileType::platform | TileType::right);
		pLevelComp->AddTile({ 2,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 3,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 4,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 5,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 6,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 7,2 }, TileType::left		| TileType::right	| TileType::bottom);
		pLevelComp->AddTile({ 8,2 }, TileType::left		| TileType::right	| TileType::bottom);



		
	}
	scene->Add(pLevel);
#pragma endregion

	// ====================================================================================
	// Burger objects
	// ====================================================================================


	//go = new GameObject("Bun Bottom");
	//{
	//	auto pTransform = go->AddComponent(new TransformComponent(go, 50, 140));
	//	auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));
	//	go->AddComponent(new BurgerComponent(go, pRender, BurgerComponent::bunBottom));
	//}
	//scene->Add(go);

	//go = new GameObject("Cheese");
	//{
	//	auto pTransform = go->AddComponent(new TransformComponent(go, 50, 220));
	//	auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));
	//	go->AddComponent(new BurgerComponent(go, pRender, BurgerComponent::cheese));
	//}
	//scene->Add(go);

	//go = new GameObject("Burger");
	//{
	//	auto pTransform = go->AddComponent(new TransformComponent(go, 50, 300));
	//	auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));
	//	go->AddComponent(new BurgerComponent(go, pRender, BurgerComponent::burger));
	//}
	//scene->Add(go);

	//go = new GameObject("Tomato");
	//{
	//	auto pTransform = go->AddComponent(new TransformComponent(go, 50, 380));
	//	auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));
	//	go->AddComponent(new BurgerComponent(go, pRender, BurgerComponent::tomato));
	//}
	//scene->Add(go);

	//go = new GameObject("Salad");
	//{
	//	auto pTransform = go->AddComponent(new TransformComponent(go, 50, 460));
	//	auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));
	//	go->AddComponent(new BurgerComponent(go, pRender, BurgerComponent::salad));
	//}
	//scene->Add(go);

	// =======================================================================================
	// =======================================================================================

	//auto* pPointsDisplay = new GameObject("PointDisplay");
	//{
	//	const auto pTransform = pPointsDisplay->AddComponent(new TransformComponent(pPointsDisplay, 100, 40));
	//	const auto pRender = pPointsDisplay->AddComponent(new RenderComponent(pPointsDisplay, pTransform));
	//	const auto pText = pPointsDisplay->AddComponent(new TextComponent(pPointsDisplay, pRender, "", pFont, { 255, 0, 0,255 }));

	//	pPointsDisplay->AddComponent(new PointsDisplayComponent(pPointsDisplay, pText));
	//}
	//scene->Add(pPointsDisplay);

	//pPointsDisplay = new GameObject("PointDisplay2");
	//{
	//	const auto pTransform = pPointsDisplay->AddComponent(new TransformComponent(pPointsDisplay, 100, 290));
	//	const auto pRender = pPointsDisplay->AddComponent(new RenderComponent(pPointsDisplay, pTransform));
	//	const auto pText = pPointsDisplay->AddComponent(new TextComponent(pPointsDisplay, pRender, "", pFont, { 0, 255, 0,255 }));

	//	pPointsDisplay->AddComponent(new PointsDisplayComponent(pPointsDisplay, pText));
	//}
	//scene->Add(pPointsDisplay);
}

void Tribe::Run()
{
	ServiceLocator::SetSoundManager(new SoundManager());
	ServiceLocator::SetEventManager(new EventManager());

	// intitializes the window
	RenderManager::Init();

	// tell the resource manager where he can find the game data
	ResourceManager::Init("../Data/");

	LoadGame();
	{			
		Timer::Start();
		for (bool running = true; running;)
		{
			// update all time related info
			Timer::Update();

			// process an input
			running = InputManager::ProcessInput();


			SceneManager::Update();

			RenderManager::Render();
			
			
			this_thread::sleep_for(Timer::GetSleepTime());
		}
	}

	SafeDelete(ServiceLocator::GetEventManager());
	SafeDelete(ServiceLocator::GetSoundManager());
}
