#include "GamePCH.h"
#include "BulletComponent.h"

#include "TransformComponent.h"

BulletComponent::BulletComponent(GameObject* pGo, TransformComponent* pTrans)
	: Component(pGo)
	, m_pTransform(pTrans)
{
	
}

BulletComponent::~BulletComponent()
{
	
}

void BulletComponent::Update(GameContext&)
{
	
}

void BulletComponent::Render() const
{
	
}
