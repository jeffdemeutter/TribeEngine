#include "TribePCH.h"
#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Texture2D.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform)
	: Component(go)
	, m_pTransformComponent(pTransform)
{
}

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform, const std::string& texturePath)
	: Component(go)
	, m_pTexture(ResourceManager::LoadTexture(texturePath))
	, m_pTransformComponent(pTransform)
{
}

RenderComponent::~RenderComponent()
{
	m_pTransformComponent = nullptr;
	m_pTexture = nullptr;
}


void RenderComponent::Render() const
{
	if (!m_pTexture)
		return;

	if (m_SrcRect.has_value())
	{
		m_pTexture->Draw(m_pTransformComponent->GetPosition(), m_SrcRect.value(), m_Rotation, m_Flip);
		return;
	}

	m_pTexture->Draw(m_pTransformComponent->GetPosition(), m_Rotation, m_Flip);
}
