#pragma once
#include <unordered_map>
#include <typeinfo>

#include "ObjectBase.h"

class Component;

class GameObject final : public ObjectBase
{
public:
	~GameObject() override;
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) noexcept = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) noexcept = delete;
	
	GameObject(ObjectBase* pParent, const std::string& objectName = "DefaultObject");


	template <typename T> T* AddComponent(T* pComponent);
	template <typename T> T* GetComponent() const;
	template <typename T> void RemoveComponent();

	ObjectBase* GetParent() const { return m_pParent; }

protected:
	friend class Scene;
	friend class ObjectBase; // this ensures we can call render and update from within the baseclass
	virtual void Render() const override;
	virtual void Update() override;
private:
	std::unordered_map<const std::type_info*, Component*> m_pComponents{};
	
	ObjectBase* m_pParent = nullptr;
};


template <typename T>
T* GameObject::AddComponent(T* pComponent)
{
	m_pComponents[&typeid(T)] = pComponent;
	return pComponent;
}

template <typename T>
T* GameObject::GetComponent() const
{
	const auto d = &typeid(T);

	if (m_pComponents.contains(d))
		return static_cast<T*>(m_pComponents.at(d));

	// component does not exist
	return nullptr;
}

template <typename T>
void GameObject::RemoveComponent()
{
	T* comp = static_cast<T*>(m_pComponents.at(&typeid(T)));

	SafeDelete(comp);

	m_pComponents.erase(&typeid(T));
}