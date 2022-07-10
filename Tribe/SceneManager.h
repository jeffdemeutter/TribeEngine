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

	std::shared_ptr<Scene> AddScene(const std::string& sceneName);
	std::shared_ptr<Scene> GetScene(const std::string& name);
	void ActivateScene(int sceneIndex);
	void ActivateScene(const std::string& sceneName);

private:
	std::vector<std::shared_ptr<Scene>> m_pScenes;
	int m_ActiveSceneIndex = 0;

	friend class Tribe;
	void Update() const;
	void Render() const;
};

