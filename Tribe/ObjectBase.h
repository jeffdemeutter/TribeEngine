#pragma once

class GameObject;

class ObjectBase
{
public:
	ObjectBase(const std::string& name) : m_Name(name) {}
	virtual ~ObjectBase();
	ObjectBase(const ObjectBase&) = delete;
	ObjectBase(ObjectBase&&) noexcept = delete;
	ObjectBase& operator=(const ObjectBase&) = delete;
	ObjectBase& operator=(ObjectBase&&) noexcept = delete;

	virtual void Update(GameContext&);
	virtual void Render() const;

	GameObject* AddGameObject(const std::string& objectName);
	GameObject* AddGameObject(GameObject* pObject);
	GameObject* AddSharedObject(GameObject* pObject);
	[[nodiscard]] GameObject* GetGameObjectByName(const std::string& objectName) const;
	void RemoveChild(GameObject* pGameObject, bool immediate = false);
	const std::string& GetName() const { return m_Name; }
	const std::vector<GameObject*>& GetGameObjects() const { return m_pGameObjects; }

	bool IsActive() const { return m_IsActivated; }
	void Activate();
	void Deactivate();
	void SetActive(bool active);
	void ToggleActive();

protected:
	std::vector<GameObject*> m_pSharedObjects;
	std::vector<GameObject*> m_pGameObjects;
	std::vector<GameObject*> m_pGameObjectsToDelete;
	std::string m_Name = "Default";

private:
	bool m_IsActivated = true;

	void DeleteObject(GameObject* pGameObject);
};

