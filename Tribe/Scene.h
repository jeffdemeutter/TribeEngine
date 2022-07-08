#pragma once

class GameObject;

class Scene
{
public:
	Scene(const std::string& name = "DefaultScene") : m_Name(name) {}
	~Scene() = default;
	Scene(const Scene&) = delete;
	Scene(Scene&&) noexcept = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) noexcept = delete;

	void AddGameObject(std::shared_ptr<GameObject> pGo);
	const std::string& GetName() const { return m_Name; }

private:
	std::vector<std::shared_ptr<GameObject>> m_pGameObjects;
	std::string m_Name = "DefaultScene";


	friend class RenderManager;
	void Render() const;
	friend class SceneManager;
	void Update();
};

