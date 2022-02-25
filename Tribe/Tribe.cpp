#include "TribePCH.h"
#include "Tribe.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"

#include "Components.h"


using namespace std;

/**
 * Code constructing the scene world starts here
 */
void Tribe::LoadGame() const
{
	Scene* scene = SceneManager::CreateScene("Demo");

	// background
	auto go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		go->AddComponent(new RenderComponent(go, pTransform, "background.jpg", true));
	}
	scene->Add(go);

	// logo
	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 216, 180));
		go->AddComponent(new RenderComponent(go, pTransform, "logo.png"));
	}
	scene->Add(go);

	// text object
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 80, 20));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		go->AddComponent(new TextComponent(go, pRender, "Programming 4 Assignment", pFont, {255,255,255,255}));
	}
	scene->Add(go);

	// fps object
	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		const auto pText = go->AddComponent(new TextComponent(go, pRender, " ", pFont, { 255,255,0,255 }));
		go->AddComponent(new FpsComponent(go, pText));
	}
	scene->Add(go);
}

void Tribe::Run()
{
	// intitializes the window
	RenderManager::Init();

	// tell the resource manager where he can find the game data
	ResourceManager::Init("../Data/");

	LoadGame();

	{			
		Timer::Start();
		bool doContinue = true;
		while (doContinue)
		{
			// update all time related info
			Timer::Update();

			// process an input
			doContinue = InputManager::ProcessInput();


			SceneManager::Update();

			RenderManager::Render();
			
			
			this_thread::sleep_for(Timer::GetSleepTime());
		}
	}
}
