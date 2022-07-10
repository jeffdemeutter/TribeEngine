#pragma once
#include <unordered_map>

class Component;

class GameObject
{
public:
	GameObject(const std::string& objectName) : m_Name(objectName){}
	~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) noexcept = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) noexcept = delete;

	template <typename T> T* AddComponent(T* pComponent);
	template <typename T> T* GetComponent() const;
	template <typename T> void RemoveComponent();

	void AddChild(GameObject* go);

protected:
	friend class Scene;
	void Render() const;
	void Update();

	void SetParent(GameObject* pGo) { m_pParent = pGo; }

private:
	std::unordered_map<const std::type_info*, Component*> m_pComponents{};
	std::vector<GameObject*> m_pChildren{};
	GameObject* m_pParent = nullptr;

	const std::string m_Name = "DefaultObject";
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