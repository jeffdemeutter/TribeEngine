#pragma once
#include "TransformComponent.h"
#include <unordered_map>
#include <typeinfo>

class Component;
class GameObject final
{
public:
	GameObject(std::string&& name = "default") : m_ObjectName(name) {}
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
	
	void AddChild(GameObject* go);

	void SetName(const std::string& name) { m_ObjectName = name; }
	const std::string& GetName() const { return m_ObjectName; }

protected:
	void SetParent(GameObject* go)
	{
		m_pParent = go;
	}

private:
	std::string m_ObjectName = "default";
	std::unordered_map<const std::type_info*, Component*> m_pComponents{};
	std::vector<GameObject*> m_pChildren{};
	GameObject* m_pParent = nullptr;
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

	if (m_pComponents.find(d) != m_pComponents.cend())
		return static_cast<T*>(m_pComponents.at(d));

	// component does not exist
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

