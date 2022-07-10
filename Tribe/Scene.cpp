#include "TribePCH.h"
#include "Scene.h"

#include "GameObject.h"


void Scene::AddGameObject(GameObject* pGo)
{
	m_pGameObjects.emplace_back(pGo);
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