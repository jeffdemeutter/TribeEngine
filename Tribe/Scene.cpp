#include "TribePCH.h"
#include "Scene.h"

#include "GameObject.h"


GameObject* Scene::AddGameObject(const std::string& objectName)
{
	return m_pGameObjects.emplace_back(new GameObject(objectName));
}

Scene::~Scene()
{
	for (const auto pGameObject : m_pGameObjects)
		SafeDelete(pGameObject);
}

void Scene::Render() const
{
	for (const auto pGameObject : m_pGameObjects)
		pGameObject->Render();
}

void Scene::Update()
{
	for (const auto pGameObject : m_pGameObjects)
		pGameObject->Update();
} 