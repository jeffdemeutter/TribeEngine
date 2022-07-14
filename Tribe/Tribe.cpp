#include "TribePCH.h"
#include "Tribe.h"

#include "GameTime.h"

#include "SoundManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include "ServiceLocator.h"


void Tribe::Run()
{
	RenderManager::Init();
	ResourceManager::Init("../Data/");

	m_GameContext.pInput		= new InputManager();
	m_GameContext.pTime			= new GameTime();
	m_GameContext.pSceneManager = new SceneManager();
	ServiceLocator::SetSoundManager(new SoundManager());
	//ServiceLocator::SetEventManager(new EventManager());

	LoadGame();
	{
		m_GameContext.pTime->Start();
		for (bool running = true; running;)
		{
			// update all time related info
			m_GameContext.pTime->Update();

			// process inputs
			running = m_GameContext.pInput->ProcessInput();

			// update scenes
			m_GameContext.pSceneManager->Update(m_GameContext);

			// render scene to window
			m_GameContext.pSceneManager->Render();
			
			// let the main thread sleep 
			std::this_thread::sleep_for(m_GameContext.pTime->GetSleepTime());
		}
	}

	//SafeDelete(ServiceLocator::GetEventManager());
	SafeDelete(ServiceLocator::GetSoundManager());
	SafeDelete(m_GameContext.pSceneManager);
	SafeDelete(m_GameContext.pTime);
	SafeDelete(m_GameContext.pInput);

	RenderManager::Destroy();
	ResourceManager::Destroy();
}
