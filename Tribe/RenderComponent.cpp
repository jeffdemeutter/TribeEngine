#include "TribePCH.h"
#include "RenderComponent.h"

#include "RenderManager.h"

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform)
	: Component(go)
	, m_pTransformComponent(pTransform)
{
}

RenderComponent::~RenderComponent()
{
	m_pTransformComponent = nullptr;
}


void RenderComponent::Render() const
{
	//if (!m_pTexture)
	//	return;

	//if (m_FillScreen)
	//{
	//	m_pTexture->DrawFillScreen();
	//	return;
	//}

	//if (m_SrcRect.has_value())
	//{
	//	m_pTexture->Draw(m_pTransformComponent->GetPosition(), m_SrcRect.value());
	//	return;
	//}

	//m_pTexture->Draw(m_pTransformComponent->GetPosition());
}
