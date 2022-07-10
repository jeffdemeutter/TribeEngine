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

	virtual void Update();
	virtual void Render() const;

	[[nodiscard]] GameObject* AddGameObject(const std::string& objectName);
	[[nodiscard]] GameObject* GetGameObjectByName(const std::string& objectName) const;
	const std::string& GetName() const { return m_Name; }

protected:
	std::vector<GameObject*> m_pGameObjects;
	std::string m_Name = "Default";
};

