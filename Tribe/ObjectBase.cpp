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
