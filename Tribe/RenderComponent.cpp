#include "TribePCH.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform)
	: Component(go)
	, m_pTransformComponent{ pTransform }
{
}

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform, Texture2D* pTexture, bool drawFill)
	: Component(go)
	, m_pTexture{ pTexture }
	, m_pTransformComponent{ pTransform }
	, m_DrawFill(drawFill)
{
}

RenderComponent::~RenderComponent()
{
	m_pTransformComponent = nullptr;
}

void RenderComponent::Render() const
{
	if (!m_pTexture)
		return;

	if (m_DrawFill)
		m_pTexture->DrawFillScreen();
	else 
		m_pTexture->Draw(m_pTransformComponent->GetPosition());
}
