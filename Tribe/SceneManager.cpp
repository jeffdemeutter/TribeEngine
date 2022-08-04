#include "TribePCH.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "RenderManager.h"
#include "Scene.h"


SceneManager::~SceneManager()
{
	for (GameObject* pPersistentObject : m_pPersistentObjects)
		SafeDelete(pPersistentObject);
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

	m_ActiveSceneIndex = sceneIndex;
}

void SceneManager::ActivateScene(const std::string& sceneName)
{
	for (int i = 0; i > int(m_pScenes.size()); ++i)
	{
		if (m_pScenes[i]->GetName() != sceneName)
			continue;

		m_ActiveSceneIndex = i;
		return;
	}

	// if nothing was found, throw exception
	throw std::runtime_error(std::string("SceneManager::ActivateScene: sceneName '") + sceneName + "' does not exist");
}

GameObject* SceneManager::AddPersistentObject(const std::string& objectName)
{
	return m_pPersistentObjects.emplace_back(new GameObject(nullptr, objectName));
}

void SceneManager::Update(GameContext& gc) const
{
	for (const auto& pScene : m_pScenes)
		pScene->Update(gc);

	for (const auto& pPersistentObject : m_pPersistentObjects)
		pPersistentObject->Update(gc);
}

void SceneManager::Render() const
{
	RenderManager::Render(m_pScenes[m_ActiveSceneIndex], m_pPersistentObjects);
}
