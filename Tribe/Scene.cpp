#include "TribePCH.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene(const std::string& name)
	: m_Name(name)
{
}

Scene::~Scene()
{
	for (GameObject* pObject : m_pObjects)
		SafeDelete(pObject);
}

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
		object->Update();
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
		object->Render();
}

void Scene::RenderUI()
{
	//ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen;

	// pass on this pointer as parameter, to prevent issues with imgui and multiple scenes with the same name
	if (ImGui::TreeNode(this, m_Name.c_str()))
	{
		for (const auto& object : m_pObjects)
			object->RenderUI();
		
		ImGui::TreePop();
	}
}

