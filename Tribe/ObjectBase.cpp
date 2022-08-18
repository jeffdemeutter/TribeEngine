#include "TribePCH.h"
#include "ObjectBase.h"

#include "EventManager.h"
#include "GameObject.h"
#include "ServiceLocator.h"

ObjectBase::~ObjectBase()
{
	for (GameObject* pChild : m_pGameObjects)
		SafeDelete(pChild);

	m_pSharedObjects.clear();
}

void ObjectBase::Update(GameContext& gc)
{
	for (const auto pGameObject : m_pGameObjects)
		if (pGameObject->IsActive())
			pGameObject->Update(gc);

	for (GameObject* pSharedObject : m_pSharedObjects)
		pSharedObject->Update(gc);

	// deleting oobjects
	if (m_pGameObjectsToDelete.empty())
		return;
	
	for (auto& pGameObjectToDelete : m_pGameObjectsToDelete)
	{
		DeleteObject(pGameObjectToDelete);
	}

	m_pGameObjectsToDelete.clear();
}

void ObjectBase::Render() const
{
	for (const auto pGameObject : m_pGameObjects)
		if (pGameObject->IsActive())
			pGameObject->Render();

	for (GameObject* pSharedObject : m_pSharedObjects)
		pSharedObject->Render();
}

GameObject* ObjectBase::AddGameObject(const std::string& objectName)
{
	return m_pGameObjects.emplace_back(new GameObject(this, objectName));
}

GameObject* ObjectBase::AddGameObject(GameObject* pObject)
{
	return m_pGameObjects.emplace_back(pObject);	
}

GameObject* ObjectBase::AddSharedObject(GameObject* pObject)
{
	return m_pSharedObjects.emplace_back(pObject);	
}

GameObject* ObjectBase::GetGameObjectByName(const std::string& objectName) const
{
	auto findIt = std::ranges::find_if(m_pGameObjects, [&objectName](GameObject* pGo) { return objectName == pGo->GetName(); });

	if (findIt == m_pGameObjects.cend())
		return nullptr;

	return *findIt;
}

void ObjectBase::RemoveChild(GameObject* pGameObject, bool immediate)
{
	if (immediate)
		DeleteObject(pGameObject);
	else 
		m_pGameObjectsToDelete.emplace_back(pGameObject);
}

void ObjectBase::Activate()
{
	m_IsActivated = true;

	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Activate();
}

void ObjectBase::Deactivate()
{
	m_IsActivated = false;

	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Deactivate();
}

void ObjectBase::SetActive(bool active)
{
	m_IsActivated = active;

	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->SetActive(active);
}

void ObjectBase::ToggleActive()
{
	m_IsActivated = !m_IsActivated;

	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->SetActive(m_IsActivated);
}

void ObjectBase::DeleteObject(GameObject* pGameObject)
{
	if (auto it = std::ranges::find(m_pGameObjects, pGameObject);
		it != m_pGameObjects.cend())
	{
		ServiceLocator::GetEventManager()->Notify(*it, GameobjectDeleted);
		SafeDelete(*it);
		m_pGameObjects.erase(it);
	}
}
