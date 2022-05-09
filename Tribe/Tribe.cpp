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

#pragma region Level
	//===========================================================================================
	// Level stuff
	//===========================================================================================
	const auto pLevel = new GameObject("Level");
	TileComponent* pStrtTile;
	{
		LevelComponent* pLevelComp = pLevel->AddComponent(new LevelComponent(pLevel, 10, "tilesprites.png", { 24, 16 }));

					pLevelComp->AddTile(0, 0, TileType::bottom | TileType::right);
					pLevelComp->AddTile(1, 0, TileType::platform);
					pLevelComp->AddTile(2, 0, TileType::left | TileType::right | TileType::bottom);
		auto bun0 = pLevelComp->AddTile(3, 0, TileType::bottom | TileType::platform);
					pLevelComp->AddTile(4, 0, TileType::left | TileType::right | TileType::bottom);
		auto bun1 = pLevelComp->AddTile(5, 0, TileType::platform);
					pLevelComp->AddTile(6, 0, TileType::left | TileType::right | TileType::bottom);
		auto bun2 = pLevelComp->AddTile(7, 0, TileType::platform);
					pLevelComp->AddTile(8, 0, TileType::left | TileType::bottom);


					pLevelComp->AddTile(0, 1, TileType::ladder);
					pLevelComp->AddTile(2, 1, TileType::ladder);
					pLevelComp->AddTile(3, 1, TileType::ladder);
					pLevelComp->AddTile(4, 1, TileType::ladder);
					pLevelComp->AddTile(6, 1, TileType::ladder);
					pLevelComp->AddTile(8, 1, TileType::ladder);


					pLevelComp->AddTile(0, 2, TileType::top | TileType::right);
		auto bun3 = pLevelComp->AddTile(1, 2, TileType::platform | TileType::bottom);
					pLevelComp->AddTile(2, 2, TileType::left | TileType::bottom | TileType::top);
					pLevelComp->AddTile(3, 2, TileType::ladder);
					pLevelComp->AddTile(4, 2, TileType::right | TileType::bottom | TileType::top);
		auto sld2 = pLevelComp->AddTile(5, 2, TileType::bottom | TileType::platform);
					pLevelComp->AddTile(6, 2, TileType::left | TileType::right | TileType::bottom | TileType::top);
		auto sld3 = pLevelComp->AddTile(7, 2, TileType::platform);
					pLevelComp->AddTile(8, 2, TileType::left | TileType::top | TileType::bottom);


					pLevelComp->AddTile(1, 3, TileType::ladder);
					pLevelComp->AddTile(2, 3, TileType::left | TileType::right | TileType::bottom | TileType::top);
					pLevelComp->AddTile(3, 3, TileType::top | TileType::platform);
					pLevelComp->AddTile(4, 3, TileType::left | TileType::right | TileType::bottom | TileType::top);
					pLevelComp->AddTile(5, 3, TileType::ladder);
					pLevelComp->AddTile(6, 3, TileType::ladder);
					pLevelComp->AddTile(8, 3, TileType::ladder);


					pLevelComp->AddTile(0, 4, TileType::bottom | TileType::right);
		auto sld0 = pLevelComp->AddTile(1, 4, TileType::platform | TileType::top | TileType::bottom);
					pLevelComp->AddTile(2, 4, TileType::left | TileType::right | TileType::bottom | TileType::top);
					pLevelComp->AddTile(4, 4, TileType::ladder);
					pLevelComp->AddTile(5, 4, TileType::ladder);
					pLevelComp->AddTile(6, 4, TileType::right | TileType::bottom | TileType::top);
		auto brg3 = pLevelComp->AddTile(7, 4, TileType::bottom | TileType::platform);
					pLevelComp->AddTile(8, 4, TileType::left | TileType::top);


					pLevelComp->AddTile(0, 5, TileType::ladder);
					pLevelComp->AddTile(1, 5, TileType::ladder);
					pLevelComp->AddTile(2, 5, TileType::right | TileType::bottom | TileType::top);
		auto sld1 = pLevelComp->AddTile(3, 5, TileType::right | TileType::left | TileType::platform);
					pLevelComp->AddTile(4, 5, TileType::right | TileType::left | TileType::top | TileType::bottom);
		auto brg2 = pLevelComp->AddTile(5, 5, TileType::top | TileType::platform);
					pLevelComp->AddTile(6, 5, TileType::left | TileType::bottom | TileType::top);
					pLevelComp->AddTile(7, 5, TileType::ladder);


					pLevelComp->AddTile(0, 6, TileType::ladder);
					pLevelComp->AddTile(1, 6, TileType::ladder);
					pLevelComp->AddTile(2, 6, TileType::ladder);
					pLevelComp->AddTile(4, 6, TileType::ladder);
					pLevelComp->AddTile(6, 6, TileType::right | TileType::bottom | TileType::top);
		auto bot3 = pLevelComp->AddTile(7, 6, TileType::platform | TileType::top | TileType::bottom);
					pLevelComp->AddTile(8, 6, TileType::left | TileType::bottom);


					pLevelComp->AddTile(0, 7, TileType::top | TileType::right | TileType::bottom);
		auto brg0 = pLevelComp->AddTile(1, 7, TileType::platform | TileType::top);
					pLevelComp->AddTile(2, 7, TileType::top | TileType::bottom | TileType::right | TileType::left);
		auto brg1 = pLevelComp->AddTile(3, 7, TileType::platform);
					pLevelComp->AddTile(4, 7, TileType::top | TileType::bottom | TileType::right | TileType::left);
					pLevelComp->AddTile(5, 7, TileType::platform);
					pLevelComp->AddTile(6, 7, TileType::left | TileType::bottom | TileType::top);
					pLevelComp->AddTile(7, 7, TileType::ladder);
					pLevelComp->AddTile(8, 7, TileType::ladder);


					pLevelComp->AddTile(0, 8, TileType::ladder);
					pLevelComp->AddTile(2, 8, TileType::ladder);
					pLevelComp->AddTile(4, 8, TileType::ladder);
					pLevelComp->AddTile(6, 8, TileType::ladder);
					pLevelComp->AddTile(7, 8, TileType::ladder);
					pLevelComp->AddTile(8, 8, TileType::ladder);


					pLevelComp->AddTile(0, 9, TileType::top | TileType::right);
		auto bot0 = pLevelComp->AddTile(1, 9, TileType::platform);
					pLevelComp->AddTile(2, 9, TileType::top | TileType::right | TileType::left);
		auto bot1 = pLevelComp->AddTile(3, 9, TileType::platform);
		pStrtTile = pLevelComp->AddTile(4, 9, TileType::top | TileType::right | TileType::left);
		auto bot2 = pLevelComp->AddTile(5, 9, TileType::platform);
					pLevelComp->AddTile(6, 9, TileType::left | TileType::top | TileType::right);
					pLevelComp->AddTile(7, 9, TileType::platform | TileType::top);
					pLevelComp->AddTile(8, 9, TileType::left | TileType::top);

		// adding the burger gameobjects
		bun0->AddBurgerObject(BurgerComponent::bunTop	);
		bun1->AddBurgerObject(BurgerComponent::bunTop	);
		bun2->AddBurgerObject(BurgerComponent::bunTop	);
		bun3->AddBurgerObject(BurgerComponent::bunTop	);
		sld0->AddBurgerObject(BurgerComponent::salad	);
		sld1->AddBurgerObject(BurgerComponent::salad	);
		sld2->AddBurgerObject(BurgerComponent::salad	);
		sld3->AddBurgerObject(BurgerComponent::salad	);
		brg0->AddBurgerObject(BurgerComponent::burger	);
		brg1->AddBurgerObject(BurgerComponent::burger	);
		brg2->AddBurgerObject(BurgerComponent::burger	);
		brg3->AddBurgerObject(BurgerComponent::burger	);
		bot0->AddBurgerObject(BurgerComponent::bunBottom);
		bot1->AddBurgerObject(BurgerComponent::bunBottom);
		bot2->AddBurgerObject(BurgerComponent::bunBottom);
		bot3->AddBurgerObject(BurgerComponent::bunBottom);

		// plateaus

		// add playerobjects to level
	}
	scene->Add(pLevel);
#pragma endregion

	auto* pPeterPepper = new GameObject("PeterPepper");
	{
		const auto pTrans = pPeterPepper->AddComponent(new TransformComponent(pPeterPepper, pStrtTile->GetPosition()));
		const auto pRender = pPeterPepper->AddComponent(new RenderComponent(pPeterPepper, pTrans, "spritesheet.png"));
		const auto pAnimator = pPeterPepper->AddComponent(new SpriteAnimationComponent(pPeterPepper, pRender, 12));

		auto pPeter = pPeterPepper->AddComponent(new PeterPepperComponent(pPeterPepper, pAnimator));

		InputManager::InputAction input;
			input.keyboardKey = SDL_SCANCODE_D;
			input.pCommand = new Command([pPeter] { pPeter->DoDamage(); });
			input.ControllerButton = VK_PAD_X;
			input.ControllerStroke = XINPUT_KEYSTROKE_KEYUP;
		InputManager::AddInputMethod(input);
	}
	scene->Add(pPeterPepper);



	// fps object
	auto go = new GameObject("Fps object");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		const auto pText = go->AddComponent(new TextComponent(go, pRender, " ", pFont, { 255,255,0,255 }));
		go->AddComponent(new FpsComponent(go, pText));
	}
	scene->Add(go);
	

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
