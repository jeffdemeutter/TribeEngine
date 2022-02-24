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


	static void Init() { GetInstance().InitImpl(); }
	static void Render() { GetInstance().RenderImpl(); }

	static SDL_Renderer* GetSDLRenderer() { return GetInstance().m_Renderer; }
	static SDL_Rect GetWindowRect() { return { 0, 0, GetInstance().m_Width, GetInstance().m_Height }; }
	static SDL_Color GetBackgroundColor() { return GetInstance().m_ClearColor; }
	static void SetBackgroundColor(const SDL_Color& color) { GetInstance().m_ClearColor = color; }

private:
	friend class Singleton<RenderManager>;
	RenderManager() = default;

	int m_Width = 640;
	int m_Height = 480;
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_ClearColor{};


	void InitImpl();
	void RenderImpl() const;

	friend class InputManager;
	static void UpdateWindow(int width, int height);
};


