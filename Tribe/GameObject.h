#pragma once
#include "TransformComponent.h"
#include <unordered_map>

class Component;
class GameObject final
{
public:
	GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;
	~GameObject();

	template <typename T> T* AddComponent(T* pComponent);
	template <typename T> T* GetComponent() const;
	template <typename T> void RemoveComponent();

	void Update();
	void Render() const;
	void RenderUI();

private:
	std::unordered_map<const std::type_info*, Component*> m_pComponents{};
	std::vector<GameObject*> m_pChildren{};
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
	if (Component* comp = m_pComponents.at(d))
		return static_cast<T*>(comp);

	return nullptr;
}

template <typename T>
void GameObject::RemoveComponent()
{
	T* comp = static_cast<T*>(m_pComponents.at(&typeid(T)));
	delete comp;
	comp = nullptr;
	m_pComponents.erase(&typeid(T));
}

