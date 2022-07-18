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

	void SetTexture(Texture2D* pTexture) { m_pTexture = pTexture; }
	void SetSrcRect(const SDL_Rect& srcRect) { m_SrcRect = srcRect; }
	void SetRotation(float rotation) { m_Rotation = rotation; }
	void SetPivot(const glm::vec2& pivot) { m_Pivot = pivot; }
	void SetCenter(const glm::vec2& center) { m_Center = center; }
	void SetFlip(SDL_RendererFlip flip) { m_Flip = flip; }

private:
	Texture2D* m_pTexture = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;

	glm::vec2 m_Center = { 0,0 };
	glm::vec2 m_Pivot = { 0,0 };
	float m_Rotation = 0.f;
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;

	std::optional<SDL_Rect> m_SrcRect;
};

