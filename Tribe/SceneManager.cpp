#include "TribePCH.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "RenderManager.h"
#include "Scene.h"


SceneManager::~SceneManager()
{
}

std::shared_ptr<Scene> SceneManager::AddScene(const std::string& sceneName)
{
	return m_pScenes.emplace_back(std::make_shared<Scene>(sceneName));
}

std::shared_ptr<Scene> SceneManager::GetScene(const std::string& name)
{
	return *std::ranges::find_if(m_pScenes, 
		[&name](std::shared_ptr<Scene> pscene) { return name == pscene->GetName(); });	
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return m_pScenes[m_ActiveSceneIndex];
}

void SceneManager::ActivateScene(int sceneIndex)
{
	if (sceneIndex >=  static_cast<int>(m_pScenes.size()))
		throw std::runtime_error(std::string("SceneManager::ActivateScene: sceneIndex '") + std::to_string(sceneIndex) + "' out of bounds");

	GetActiveScene()->Deactivate();
	m_ActiveSceneIndex = sceneIndex;
	GetActiveScene()->Activate();
}

void SceneManager::ActivateScene(const std::string& sceneName)
{
	for (int i = 0; i < int(m_pScenes.size()); ++i)
	{
		if (m_pScenes[i]->GetName() != sceneName)
			continue;

		ActivateScene(i);
		return;
	}

	// if nothing was found, throw exception
	throw std::runtime_error(std::string("SceneManager::ActivateScene: sceneName '") + sceneName + "' does not exist");
}

void SceneManager::Update(GameContext& gc) const
{
	for (const auto& pScene : m_pScenes)
		pScene->Update(gc);
}

void SceneManager::Render() const
{
	RenderManager::Render(m_pScenes[m_ActiveSceneIndex]);
}
