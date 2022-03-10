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
	auto go = new GameObject("Background");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		go->AddComponent(new RenderComponent(go, pTransform, "background.jpg", true));
	}
	scene->Add(go);

	// logo
	go = new GameObject("Logo");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 216, 180));
		go->AddComponent(new RenderComponent(go, pTransform, "logo.png"));
	}
	scene->Add(go);

	// text object
	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	go = new GameObject("Prog4 text");
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 80, 20));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		go->AddComponent(new TextComponent(go, pRender, "Programming 4 Assignment", pFont, {255,255,255,255}));
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

	// printer
	go = new GameObject("Printer");
	{
		const auto pPrinter = go->AddComponent(new PrinterComponent(go, "fire"));
		Command* pFire = new Command([pPrinter] { pPrinter->Print(); });
		//InputManager::AddInputMethod( XINPUT_GAMEPAD_A, XINPUT_KEYSTROKE_KEYUP, pFire);
		InputManager::AddInputMethod(VK_GAMEPAD_A, XINPUT_KEYSTROKE_KEYUP, pFire);
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
}
