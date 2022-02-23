#pragma once
#include "SceneManager.h"

class GameObject;
class Scene final
{
	friend class SceneManager;
public:
	void Add(GameObject* object);
	
	void Update();
	void Render() const;
	void RenderUI();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	std::string m_Name = "DefaultScene";
	std::vector <GameObject*> m_pObjects{};
};
