#pragma once

class GameObject;
class Component
{
public:
	Component(GameObject* pGo)
		: m_pParent(pGo)
	{
	}
	virtual ~Component()
	{
		m_pParent = nullptr; // these objects should be deleted by the scene
	}

	virtual void Update() = 0;
	virtual void Render() const = 0;

	GameObject* GetParent() const
	{
		return m_pParent;
	}

private:
	GameObject* m_pParent;
};

