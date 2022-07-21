#include "TribePCH.h"
#include "Texture2D.h"

#include "RenderManager.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

void Texture2D::Draw(const glm::vec2& pos, const glm::vec2& pivot, float angle, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &dst.w, &dst.h);

	dst.w = int(float(dst.w) * m_SizeMultiplier);
	dst.h = int(float(dst.h) * m_SizeMultiplier);

	SDL_Point center(int(pivot.x), int(pivot.y));
	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst, double(angle), &center, flip);
}

void Texture2D::Draw(const glm::vec2& pos, const glm::vec2& pivot, const SDL_Rect& srcRect, float angle, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(srcRect.w * m_SizeMultiplier);
	dst.h = static_cast<int>(srcRect.h * m_SizeMultiplier);

	SDL_Point center(int(pivot.x), int(pivot.y));

	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, &srcRect, &dst, double(angle), &center, flip);
}

void Texture2D::DrawFillScreen(SDL_RendererFlip flip) const
{
	const SDL_Rect dst = RenderManager::GetWindowRect();
	SDL_RenderCopyEx(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst, 0, nullptr, flip);
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture(texture)
{
}
