#pragma once

class GameObject;

class Scene
{
public:
	Scene(const std::string& name = "DefaultScene") : m_Name(name) {}
	~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) noexcept = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) noexcept = delete;

	GameObject* AddGameObject(const std::string& objectName);
	const std::string& GetName() const { return m_Name; }

private:
	std::vector<GameObject*> m_pGameObjects;
	std::string m_Name = "DefaultScene";


	friend class RenderManager;
	void Render() const;
	friend class SceneManager;
	void Update();
};

