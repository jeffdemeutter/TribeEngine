#include "TribePCH.h"
#include "Tribe.h"
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Timer.h"

#include "ServiceLocator.h"

using namespace std;


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
