#pragma once
#include "ObjectBase.h"

class Scene final : public ObjectBase
{
public:
	Scene(const std::string& name = "DefaultScene") : ObjectBase(name) {}
	~Scene() override = default;
	Scene(const Scene&) = delete;
	Scene(Scene&&) noexcept = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) noexcept = delete;
	
private:
	friend class RenderManager; // lets rendermanager access Render method
	friend class SceneManager; // lets scenemanager access Update method
};

