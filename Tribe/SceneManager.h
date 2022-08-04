#pragma once

class GameObject;
class Scene;

class SceneManager final
{
public:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) noexcept = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) noexcept = delete;

	std::shared_ptr<Scene> AddScene(const std::string& sceneName);
	std::shared_ptr<Scene> GetScene(const std::string& name);
	std::shared_ptr<Scene> GetActiveScene();
	void ActivateScene(int sceneIndex);
	void ActivateScene(const std::string& sceneName);

	GameObject* AddPersistentObject(const std::string& objectName);

private:
	std::vector<std::shared_ptr<Scene>> m_pScenes;
	int m_ActiveSceneIndex = 0;

	std::vector<GameObject*> m_pPersistentObjects;

	friend class Tribe;
	void Update(GameContext& gc) const;
	void Render() const;
};

