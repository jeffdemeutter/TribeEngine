#include "TribePCH.h"
#include "Tribe.h"

//#include <thread>


void Tribe::Run()
{
	//ServiceLocator::SetSoundManager(new SoundManager());
	//ServiceLocator::SetEventManager(new EventManager());

	/////// intitializes the window
	//RenderManager::Init();

	/////// tell the resource manager where he can find the game data
	//ResourceManager::Init("../Data/");

	LoadGame();
	{
		//Timer::Start();
		for (bool running = true; running;)
		{
			// update all time related info
			//Timer::Update();

			/////// process an input
			//running = InputManager::ProcessInput();


			//SceneManager::Update();

			//RenderManager::Render();


			//std::this_thread::sleep_for(Timer::GetSleepTime());
			
		}
	}

	//SafeDelete(ServiceLocator::GetEventManager());
	//SafeDelete(ServiceLocator::GetSoundManager());
}
