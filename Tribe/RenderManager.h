#pragma once



class RenderManager final
{
public:
	RenderManager();
	~RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) noexcept = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) noexcept = delete;

	
	void Render();

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	SDL_Rect GetWindowRect() const {
		return { 0, 0, m_Width, m_Height };
	}
	SDL_Color GetBackgroundColor() const { return m_ClearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

private:
	int m_Width = 900;
	int m_Height = 600;
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_ClearColor{};
	bool m_RenderImGui = false;

	friend class InputManager;
	void UpdateWindow(int width, int height);
};

