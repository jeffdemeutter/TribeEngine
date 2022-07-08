#pragma once

class GameObject;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
	Scene(const Scene&) = delete;
	Scene(Scene&&) noexcept = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) noexcept = delete;

	


private:
	std::vector<std::shared_ptr<GameObject>> m_pGameObjects;


	friend class RenderManager;
	void Render() const;
	friend class SceneManager;
	void Update();
};

