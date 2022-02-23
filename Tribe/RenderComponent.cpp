#include "TribePCH.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform)
	: Component(go)
	, m_pTransformComponent{ pTransform }
{
}

RenderComponent::RenderComponent(GameObject* go, TransformComponent* pTransform, const std::string& pTexture)
	: Component( go )
	, m_pTexture { ResourceManager::LoadTexture(pTexture) }
	, m_pTransformComponent{ pTransform }
{
}

RenderComponent::~RenderComponent()
{
	m_pTransformComponent = nullptr;
}

void RenderComponent::Render() const
{
	if (m_pTexture)
		m_pTexture->Draw(m_pTransformComponent->GetPosition());
}
