#pragma once
#include "Singleton.h"

class RenderManager final : public Singleton<RenderManager>
{
public:
	~RenderManager() override = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) noexcept = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) noexcept = delete;

	static void Init();
	static void Render();
	static void Destroy();

	static SDL_Renderer* GetSDLRenderer();
	static SDL_Rect GetWindowRect();
	static void SetBackgroundColor(const SDL_Color& color);

private:
	friend class Singleton<RenderManager>;
	RenderManager() = default;

	class SDLRendererImpl;
	std::unique_ptr<SDLRendererImpl> m_pImpl;
	
	friend class InputManager;
	static void UpdateWindow(int width, int height);
};

