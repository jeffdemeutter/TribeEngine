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

	static void RenderTexture(SDL_Texture* pTexture, float x, float y)
		{ GetInstance().RenderTextureImpl(pTexture, x, y); }
	static void RenderTexture(SDL_Texture* pTexture, float x, float y, float width, float height)
		{ GetInstance().RenderTextureImpl(pTexture, x, y, width, height); }

	static SDL_Renderer* GetSDLRenderer() { return GetInstance().GetSDLRendererImpl(); }

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

private:
	friend class Singleton<RenderManager>;
	RenderManager() = default;
	
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_clearColor{};


	void InitImpl();
	void RenderImpl() const;
	void RenderTextureImpl(SDL_Texture* pTexture, float x, float y) const;
	void RenderTextureImpl(SDL_Texture* pTexture, float x, float y, float width, float height) const;


	SDL_Renderer* GetSDLRendererImpl() const { return m_Renderer; }
};


