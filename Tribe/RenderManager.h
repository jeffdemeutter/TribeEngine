#pragma once
#include "Singleton.h"

class Texture2D;
/**
* Simple RAII wrapper for the SDL renderer
*/
class RenderManager final : public Singleton<RenderManager>
{
public:
	~RenderManager() override;
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) noexcept = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) noexcept = delete;


	static void Init();
	static void Render();

	static SDL_Renderer* GetSDLRenderer() { return Get().m_Renderer; }
	static SDL_Rect GetWindowRect() { return { 0, 0, Get().m_Width, Get().m_Height }; }
	static SDL_Color GetBackgroundColor() { return Get().m_ClearColor; }
	static void SetBackgroundColor(const SDL_Color& color) { Get().m_ClearColor = color; }
	static void ToggleImGui() { Get().m_RenderImGui = !Get().m_RenderImGui; }

private:
	friend class Singleton<RenderManager>;
	RenderManager() = default;

	int m_Width = 900;
	int m_Height = 600;
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_ClearColor{};
	bool m_RenderImGui = true;

	friend class InputManager;
	static void UpdateWindow(int width, int height);

	void RenderUI() const;
};


