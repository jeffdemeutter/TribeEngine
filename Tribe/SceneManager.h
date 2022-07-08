#pragma once

class Scene;

class SceneManager final
{
public:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) noexcept = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) noexcept = delete;

	int AddScene(std::shared_ptr<Scene> pScene);
	void ActivateScene(int sceneIndex);
	std::shared_ptr<Scene> GetScene(int sceneIndex) const;

private:
	std::vector<std::shared_ptr<Scene>> m_pScenes;
	int m_ActiveSceneIndex = 0;

	friend class Tribe;
	void Update() const;
	void Render() const;
};

