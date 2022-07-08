#include "TribePCH.h"
#include "SceneManager.h"

#include "RenderManager.h"
#include "Scene.h"


int SceneManager::AddScene(std::shared_ptr<Scene> pScene)
{
	m_pScenes.emplace_back(std::move(pScene));

	return static_cast<int>(m_pScenes.size()) - 1;
}

void SceneManager::ActivateScene(int sceneIndex)
{
	if (sceneIndex >=  static_cast<int>(m_pScenes.size()))
		throw std::runtime_error(std::string("SceneManager::ActivateScene: sceneIndex '") + std::to_string(sceneIndex) + "' out of bounds");

	m_ActiveSceneIndex = sceneIndex;
}

std::shared_ptr<Scene> SceneManager::GetScene(int sceneIndex) const
{
	if (sceneIndex >= static_cast<int>(m_pScenes.size()))
		throw std::runtime_error(std::string("SceneManager::GetScene: sceneIndex '") + std::to_string(sceneIndex) + "' out of bounds");

	return m_pScenes[sceneIndex];
}

void SceneManager::Update() const
{
	for (const auto pScene : m_pScenes)
		pScene->Update();
}

void SceneManager::Render() const
{
	RenderManager::Render(m_pScenes[m_ActiveSceneIndex]);
}
