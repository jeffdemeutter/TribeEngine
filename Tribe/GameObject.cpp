#include "TribePCH.h"
#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"

GameObject::~GameObject()
{
	for (const auto& component : m_pComponents)
		SafeDelete(component.second);
	m_pComponents.clear();
}

GameObject::GameObject(ObjectBase* pParent, const std::string& objectName)
	: ObjectBase(objectName)
	, m_pParent(pParent)
{
}

void GameObject::Render() const
{
	const RenderComponent* const comp = GetComponent<RenderComponent>();
	if (comp)
		comp->Render();

	// calls Render on child objects
	ObjectBase::Render();
}

void GameObject::Update()
{
	for (const auto& pComponent : m_pComponents)
		pComponent.second->Update();

	// calls Update on child objects
	ObjectBase::Update();
}
