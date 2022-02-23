#include "TribePCH.h"
#include "GameObject.h"
#include "RenderComponent.h"

GameObject::~GameObject()
{
	for (GameObject* pObject : m_pChildren)
		SafeDelete(pObject);

	for (auto& component : m_pComponents)
		SafeDelete(component.second);
	m_pComponents.clear();
}

void GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
		pComponent.second->Update();
}

void GameObject::Render() const
{
	const RenderComponent* const comp = GetComponent<RenderComponent>();
	if (comp)
		comp->Render();
}

void GameObject::RenderUI()
{
	
}
