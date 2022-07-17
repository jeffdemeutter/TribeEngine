#pragma once
#include "Singleton.h"
#include "glm/glm.hpp"

class Scene;

class RenderManager final : public Singleton<RenderManager>
{
public:
	~RenderManager() override = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) noexcept = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) noexcept = delete;

	static SDL_Renderer* GetSDLRenderer() { return Instance().m_pRenderer; }
	static SDL_Rect GetWindowRect()
	{
		return { 0, 0, Instance().m_Width, Instance().m_Height };
	}
	static glm::vec2 GetWindowSize() { return {Instance().m_Width, Instance().m_Height}; }
	static glm::vec2 GetWindowCenter() { return {Instance().m_Width / 2, Instance().m_Height / 2}; }
	static void SetBackgroundColor(const SDL_Color& color)
	{
		Instance().m_ClearColor = color;
	}

private:
	friend class Singleton<RenderManager>;
	RenderManager() = default;

	int m_Width = 900;
	int m_Height = 600;
	SDL_Renderer* m_pRenderer{};
	SDL_Window* m_pWindow{};
	SDL_Color m_ClearColor{};

	
	friend class InputManager;
	static void UpdateWindow(int width, int height);

	friend class SceneManager;
	static void Render(std::shared_ptr<Scene> pScene);

	friend class Tribe;
	static void Init();
	static void Destroy();
};

