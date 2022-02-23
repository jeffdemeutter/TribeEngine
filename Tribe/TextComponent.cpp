#include "TribePCH.h"
#include <SDL2/SDL_ttf.h>
#include "Font.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "RenderManager.h"

TextComponent::TextComponent(GameObject* go, RenderComponent* pRenderComponent, const std::string& text, Font* pFont, const SDL_Color& color)
	: Component(go)
	, m_pFont{ pFont }
	, m_Color{ color }
	, m_pRenderComponent{ pRenderComponent }
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

	SafeDelete(m_pTexture);

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	const auto texture = SDL_CreateTextureFromSurface(RenderManager::GetSDLRenderer(), surf);
	if (texture == nullptr)
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surf);
	m_pTexture = new Texture2D(texture);
	m_pRenderComponent->SetTexture(m_pTexture);
}

