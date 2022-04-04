#include "TribePCH.h"
#include "Texture2D.h"

#include "RenderManager.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

void Texture2D::Draw(float x, float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst);
}

void Texture2D::Draw(float x, float y, float width, float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst);
}

void Texture2D::Draw(const glm::vec3& pos) const
{
	Draw(pos.x, pos.y);
}

void Texture2D::Draw(const glm::vec3& pos, const SDL_Rect& srcRect, float scale)
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(srcRect.w * scale);
	dst.h = static_cast<int>(srcRect.h * scale);
	SDL_RenderCopy(RenderManager::GetSDLRenderer(), m_pTexture, &srcRect, &dst);
}

void Texture2D::DrawFillScreen() const
{
	SDL_Rect dst = RenderManager::GetWindowRect();
	SDL_RenderCopy(RenderManager::GetSDLRenderer(), m_pTexture, nullptr, &dst);
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture(texture)
{
}
