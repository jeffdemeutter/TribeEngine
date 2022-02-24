#pragma once
#include "BaseComponent.h"

class Texture2D;
class TransformComponent;
class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* go, TransformComponent* pTransform);
	RenderComponent(GameObject* go, TransformComponent* pTransform, const std::string& pTexture);
	~RenderComponent() override;
	RenderComponent(const RenderComponent&) = default;
	RenderComponent(RenderComponent&&) noexcept = default;
	RenderComponent& operator=(const RenderComponent&) = default;
	RenderComponent& operator=(RenderComponent&&) noexcept = default;
	
	virtual void Update() override {}
	virtual void Render() const override;
	
	void SetTexture(Texture2D* pTexture)
	{
		m_pTexture = pTexture;
	}

private:
	Texture2D* m_pTexture = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;
};

