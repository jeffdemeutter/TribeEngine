#include "TribePCH.h"
#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"

GameObject::~GameObject()
{
	for (GameObject* pChild : m_pChildren)
		SafeDelete(pChild);

	for (auto& component : m_pComponents)
		SafeDelete(component.second);
	m_pComponents.clear();
}

void GameObject::AddChild(GameObject* go)
{
	if (!go)
		return;

	if (go == m_pParent)
		return;

	if (go == this)
		return;

	m_pChildren.emplace_back(go);
	go->SetParent(this);
}

void GameObject::Render() const
{
	const RenderComponent* const comp = GetComponent<RenderComponent>();
	if (comp)
		comp->Render();

	for (GameObject* pChild : m_pChildren)
		pChild->Render();
}

void GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
		pComponent.second->Update();

	for (GameObject* pChild : m_pChildren)
		pChild->Update();
}
