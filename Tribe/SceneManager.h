#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager() override;
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) noexcept = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) noexcept = delete;
	
	static void Update() { GetInstance().UpdateImpl(); }
	static void Render() { GetInstance().RenderImpl(); }
	static void RenderUI() { GetInstance().RenderUIImpl(); }
	static Scene* CreateScene(const std::string& name) { return GetInstance().CreateSceneImpl(name); }

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<Scene*> m_Scenes;
	
	void UpdateImpl();
	void RenderImpl() const;
	void RenderUIImpl();

	Scene* CreateSceneImpl(const std::string& name);
};



