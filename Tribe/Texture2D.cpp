#include "TribePCH.h"
#include "Texture2D.h"

#include "RenderManager.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

void Texture2D::Draw(float x, float y, float angle, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &dst.w, &dst.h);

	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst, double(angle), nullptr, flip);
}

void Texture2D::Draw(float x, float y, float width, float height, float angle, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst, double(angle), nullptr, flip);
}

void Texture2D::Draw(const glm::vec2& pos, float angle, SDL_RendererFlip flip) const
{
	Draw(pos.x, pos.y, angle, flip);
}

void Texture2D::Draw(const glm::vec2& pos, const SDL_Rect& srcRect, float angle, SDL_RendererFlip flip)
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(srcRect.w);
	dst.h = static_cast<int>(srcRect.h);
	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, &srcRect, &dst, double(angle), nullptr, flip);
}

void Texture2D::DrawFillScreen(SDL_RendererFlip flip) const
{
	SDL_Rect dst = RenderManager::GetWindowRect();
	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst, 0, nullptr, flip);
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture(texture)
{
}
