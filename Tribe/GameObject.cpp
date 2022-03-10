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

	for (GameObject* pChild : m_pChildren)
		pChild->Update();
}

void GameObject::Render() const
{
	const RenderComponent* const comp = GetComponent<RenderComponent>();
	if (comp)
		comp->Render();
}

void GameObject::RenderUI()
{
	// pass on this pointer as parameter, to prevent issues with imgui and multiple objects with the same name
	if(ImGui::TreeNode(this, m_ObjectName.c_str()))
	{
		for (GameObject* pChild : m_pChildren)
		{
			ImGui::TreeNode(pChild, pChild->GetName().c_str());

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}

void GameObject::SetParent(const GameObject*)
{
	

}
