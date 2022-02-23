#include "TribePCH.h"
#include "tribe.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"

#include "FpsComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"


using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Tribe::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL // | SDL_WINDOW_ALWAYS_ON_TOP
	);
	if (m_Window == nullptr) 
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	RenderManager::Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Tribe::LoadGame() const
{
	Scene* scene = SceneManager::CreateScene("Demo");

	auto go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		go->AddComponent(new RenderComponent(go, pTransform, "background.jpg"));
	}
	scene->Add(go);

	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 216, 180));
		go->AddComponent(new RenderComponent(go, pTransform, "logo.png"));
	}
	scene->Add(go);


	Font* pFont = ResourceManager::LoadFont("Lingua.otf", 36);
	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go, 80, 20));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		go->AddComponent(new TextComponent(go, pRender, "Programming 4 Assignment", pFont, {255,255,255,255}));
	}
	scene->Add(go);


	go = new GameObject();
	{
		const auto pTransform = go->AddComponent(new TransformComponent(go));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTransform));
		const auto pText = go->AddComponent(new TextComponent(go, pRender, " ", pFont, { 255,255,0,255 }));
		go->AddComponent(new FpsComponent(go, pText));
	}
	scene->Add(go);
}

void Tribe::Cleanup()
{
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Tribe::Run()
{
	Initialize();

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

	Cleanup();
}
