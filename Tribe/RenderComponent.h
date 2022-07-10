#pragma once
#include "Component.h"

class TransformComponent;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* go, TransformComponent* pTransform);
	~RenderComponent() override;
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) noexcept = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;

	virtual void Update() override {}
	virtual void Render() const override;

	//void SetTexture(Texture2D* pTexture)
	//{
	//	m_pTexture = pTexture;
	//}

	void SetSrcRect(const glm::fvec4& srcRect)
	{
		m_SrcRect = srcRect;
	}

private:
	//Texture2D* m_pTexture = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;

	//bool m_FillScreen = false;

	std::optional<glm::fvec4> m_SrcRect;
};
