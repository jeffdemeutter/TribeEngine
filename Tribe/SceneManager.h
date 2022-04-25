#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager() override;
	
	static void Update();
	static void Render();
	static void RenderUI();
	static Scene* CreateScene(const std::string& name);

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;

	std::vector<Scene*> m_Scenes;
};



