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

void SceneManager::Update()
{
	for(auto& scene : Get().m_Scenes)
		scene->Update();
}

void SceneManager::Render()
{
	for (const auto& scene : Get().m_Scenes)
		scene->Render();
}

void SceneManager::RenderUI()
{
	ImGui::Begin("Scenes");
	for (const auto& scene : Get().m_Scenes)
		scene->RenderUI();
	ImGui::End();
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	Scene* scene = new Scene(name);
	Get().m_Scenes.push_back(scene);
	return scene;
}
