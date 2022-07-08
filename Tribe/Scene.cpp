#include "TribePCH.h"
#include "Scene.h"

#include "GameObject.h"


void Scene::AddGameObject(std::shared_ptr<GameObject> pGo)
{
	m_pGameObjects.emplace_back(pGo);
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