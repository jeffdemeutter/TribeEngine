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

	[[nodiscard]] GameObject* AddGameObject(const std::string& objectName);
	[[nodiscard]] GameObject* GetGameObjectByName(const std::string& objectName) const;
	const std::string& GetName() const { return m_Name; }

	void Active() { m_IsActivated = true; }
	void Deactivate() { m_IsActivated = false; }
	void SetActive(bool active) { m_IsActivated = active; }
	void ToggleActive() { m_IsActivated = !m_IsActivated; }
	bool IsActive() const { return m_IsActivated; }

protected:
	std::vector<GameObject*> m_pGameObjects;
	std::string m_Name = "Default";

private:
	bool m_IsActivated = true;
};

