#include "GamePCH.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "TransformComponent.h"

BulletComponent::BulletComponent(GameObject* pGo, TransformComponent* pTrans, const glm::vec2& direction, float speed)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_Speed(speed)
	, m_Direction(normalize(direction))
{
	
}

BulletComponent::~BulletComponent()
{
	m_pTransform = nullptr;
}

void BulletComponent::Update(GameContext& gc)
{
	m_Duration += gc.pTime->GetDeltaTime();
	if (m_Duration >= m_MaxDuration)
	{
		const auto pBulletObject = GetParent();
		pBulletObject->GetParent()->RemoveGameObject(pBulletObject);
	}

	auto& pos = m_pTransform->GetRelativePosition();

	pos += m_Direction * m_Speed;


}
