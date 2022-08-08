#pragma once
#include "Component.h"

class Font;
class RenderComponent;
class Texture2D;
class TextComponent final : public Component
{
public:
	TextComponent(GameObject* go, RenderComponent* pRenderComponent, const std::string& text, Font* pFont, const SDL_Color& color = {255,255,255,255}, bool isVisible = true);
	~TextComponent() override;
	TextComponent(const TextComponent&) = default;
	TextComponent(TextComponent&&) noexcept = default;
	TextComponent& operator=(const TextComponent&) = default;
	TextComponent& operator=(TextComponent&&) noexcept = default;

	void SetText(const std::string& text);
	void SetVisibility(bool visible);
	void SetBackgroundColor(const SDL_Color& bgColor);

	// Inherited via Component
	virtual void Update(GameContext& ) override {}
	virtual void Render() const override {}

private:
	std::string m_Text = "Default";
	Font* m_pFont;
	std::optional<SDL_Color> m_BackgroundColor;
	SDL_Color m_ForegroundColor;
	bool m_IsVisible;

	Texture2D* m_pTexture = nullptr;
	RenderComponent* m_pRenderComponent = nullptr;
};

