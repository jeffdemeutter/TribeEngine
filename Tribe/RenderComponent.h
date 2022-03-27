#pragma once
#include "BaseComponent.h"

class Texture2D;
class TransformComponent;
class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* go, TransformComponent* pTransform);
	RenderComponent(GameObject* go, TransformComponent* pTransform, const std::string& pTexture, bool drawFill = false);
	~RenderComponent() override;
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) noexcept = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;
	
	virtual void Update() override {}
	virtual void Render() const override;
	
	void SetTexture(Texture2D* pTexture)
	{
		m_pTexture = pTexture;
	}

private:
	Texture2D* m_pTexture = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;

	bool m_DrawFill = false;
};

