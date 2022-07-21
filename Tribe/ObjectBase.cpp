#include "TribePCH.h"
#include "ObjectBase.h"
#include "GameObject.h"

ObjectBase::~ObjectBase()
{
	for (GameObject* pChild : m_pGameObjects)
		SafeDelete(pChild);
}

void ObjectBase::Update(GameContext& gc)
{
	for (const auto pGameObject : m_pGameObjects)
		if (pGameObject->IsActive())
			pGameObject->Update(gc);


	// deleting oobjects
	if (!m_pGameObjectsToDelete.empty())
	{
		for (auto& pGameObjectToDelete : m_pGameObjectsToDelete)
		{
			if (auto it = 	std::ranges::find(m_pGameObjects, pGameObjectToDelete); 
				it != m_pGameObjects.cend())
			{
				SafeDelete(*it);
				m_pGameObjects.erase(it);
			}
		}

		m_pGameObjectsToDelete.clear();
	}
}

void ObjectBase::Render() const
{
	for (const auto pGameObject : m_pGameObjects)
		if (pGameObject->IsActive())
			pGameObject->Render();
}

GameObject* ObjectBase::AddGameObject(const std::string& objectName)
{
	return m_pGameObjects.emplace_back(new GameObject(this, objectName));
}

GameObject* ObjectBase::GetGameObjectByName(const std::string& objectName) const
{
	auto findIt = std::ranges::find_if(m_pGameObjects, [&objectName](GameObject* pGo) { return objectName == pGo->GetName(); });

	if (findIt == m_pGameObjects.cend())
		return nullptr;

	return *findIt;
}

void ObjectBase::RemoveGameObject(GameObject* pGameObject)
{
	m_pGameObjectsToDelete.emplace_back(pGameObject);
}
