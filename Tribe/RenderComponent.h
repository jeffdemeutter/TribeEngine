#pragma once
#include "Component.h"
#include <optional>

class Texture2D;
class TransformComponent;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* go, TransformComponent* pTransform);
	RenderComponent(GameObject* go, TransformComponent* pTransform, const std::string& texturePath);
	~RenderComponent() override;
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) noexcept = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override;

	void SetTexture(Texture2D* pTexture)
	{
		m_pTexture = pTexture;
	}

	void SetSrcRect(const SDL_Rect& srcRect)
	{
		m_SrcRect = srcRect;
	}

private:
	Texture2D* m_pTexture = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;

	std::optional<SDL_Rect> m_SrcRect;
};

