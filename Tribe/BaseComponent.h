#pragma once

class GameObject;
class Component
{
public:
	Component(GameObject* go)
		: m_pParent{ go }
	{

	}
	virtual ~Component()
	{
		// gameobject get deleted by the scene(manager)
		m_pParent = nullptr;
	}
	
	virtual void Update() = 0;
	virtual void Render() const = 0;

	[[nodiscard]] GameObject* GetParent() const
	{
		return m_pParent;
	}
protected:
	GameObject* m_pParent;

};

