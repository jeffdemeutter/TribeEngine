#include "TribePCH.h"
#include "GameObject.h"
#include "RenderComponent.h"

GameObject::~GameObject()
{
	for (GameObject* pChild : m_pChildren)
		SafeDelete(pChild);

	for (auto& component : this->m_pComponents)
		SafeDelete(component.second);
	m_pComponents.clear();
}

void GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
		pComponent.second->Update();

	for (GameObject* pChild : m_pChildren)
		pChild->Update();
}

void GameObject::Render() const
{
	const RenderComponent* const comp = GetComponent<RenderComponent>();
	if (comp)
		comp->Render();

	for (GameObject* pChild : m_pChildren)
		pChild->Render();
}

void GameObject::RenderUI()
{
	// pass on this pointer as parameter, to prevent issues with imgui and multiple objects with the same name
	if(ImGui::TreeNode(this, m_ObjectName.c_str()))
	{
		for (GameObject* pChild : m_pChildren)
			pChild->RenderUI();

		ImGui::TreePop();
	}
}

void GameObject::AddChild(GameObject* go)
{
	if (!go)
		return;

	if (go == m_pParent)
		return;

	m_pChildren.push_back(go);
	go->SetParent(this);
}

