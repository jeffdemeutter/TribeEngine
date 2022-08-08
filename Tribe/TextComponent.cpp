#include "TribePCH.h"
#include <SDL2/SDL_ttf.h>
#include "Font.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "RenderManager.h"

TextComponent::TextComponent(GameObject* go, RenderComponent* pRenderComponent, const std::string& text, Font* pFont, const SDL_Color& color, bool isVisible)
	: Component(go)
	, m_pFont{ pFont }
	, m_ForegroundColor{ color }
	, m_IsVisible(isVisible)
	, m_pRenderComponent{pRenderComponent}
{
	SetText(text);
}

TextComponent::~TextComponent()
{
	SafeDelete(m_pTexture);
	// managed at ResourceManager
	m_pFont = nullptr;
	// managed by gameobject
	m_pRenderComponent = nullptr;
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;

	if (m_Text.empty())
		return;

	SafeDelete(m_pTexture);

	SDL_Surface* pSurface;
	if (m_BackgroundColor.has_value())
		pSurface = TTF_RenderText_Shaded(m_pFont->GetFont(), m_Text.c_str(), m_ForegroundColor, m_BackgroundColor.value());
	else
		pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_ForegroundColor);

	if (pSurface == nullptr)
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	const auto texture = SDL_CreateTextureFromSurface(RenderManager::GetSDLRenderer(), pSurface);
	if (texture == nullptr)
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(pSurface);
	m_pTexture = new Texture2D(texture);

	if (m_IsVisible)
		m_pRenderComponent->SetTexture(m_pTexture);
}

void TextComponent::SetVisibility(bool visible)
{
	m_IsVisible = visible;

	if (m_IsVisible)
		m_pRenderComponent->SetTexture(m_pTexture);
}

void TextComponent::SetBackgroundColor(const SDL_Color& bgColor)
{
	m_BackgroundColor = bgColor;

	m_pRenderComponent->SetTexture(m_pTexture);
}

