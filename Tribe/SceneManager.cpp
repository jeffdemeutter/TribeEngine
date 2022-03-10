#include "TribePCH.h"
#include "SceneManager.h"

#include <chrono>
#include <numeric>
using namespace std::chrono;

#include "Scene.h"


SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
		SafeDelete(pScene);	
}

void SceneManager::UpdateImpl()
{
	for(auto& scene : m_Scenes)
		scene->Update();
}

void SceneManager::RenderImpl() const
{
	for (const auto& scene : m_Scenes)
		scene->Render();
}

void SceneManager::RenderUIImpl()
{
	ImGui::Begin("Scenes");
	for (const auto& scene : m_Scenes)
		scene->RenderUI();
	ImGui::End();
}

Scene* SceneManager::CreateSceneImpl(const std::string& name)
{
	Scene* scene = new Scene(name);
	m_Scenes.push_back(scene);
	return scene;
}
