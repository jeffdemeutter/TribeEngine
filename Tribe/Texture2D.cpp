#include "TribePCH.h"
#include "Texture2D.h"

#include "RenderManager.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

void Texture2D::Draw(float x, float y) const
{
	RenderManager::RenderTexture(m_pTexture, x, y);
}

void Texture2D::Draw(const glm::vec3& pos) const
{
	RenderManager::RenderTexture(m_pTexture, pos.x, pos.y);	
}

Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture(texture)
{
}
