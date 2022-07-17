#pragma once
struct SDL_Texture;

/**
	* Simple RAII wrapper for an SDL_Texture
	*/
class Texture2D final
{
public:
	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D& operator= (const Texture2D&) = delete;
	Texture2D& operator= (const Texture2D&&) = delete;

	// normal draw calls
	void Draw(float x, float y, float angle = 0.f, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void Draw(float x, float y, float width, float height, float angle = 0.f, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void Draw(const glm::vec2& pos, float angle = 0.f, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	// source rect draw calls
	void Draw(const glm::vec2& pos, const SDL_Rect& srcRect, float angle = 0.f, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	//background draw calls
	void DrawFillScreen(SDL_RendererFlip flip = SDL_FLIP_NONE) const;

private:
	SDL_Texture* m_pTexture;
};