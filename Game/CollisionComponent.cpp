#include "GamePCH.h"
#include "CollisionComponent.h"

#include "TransformComponent.h"

CollisionComponent::CollisionComponent(GameObject* pGo, TransformComponent* pTrans, float width, float height)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_Left(-width / 2)
	, m_Right(width / 2)
	, m_Top(-height / 2)
	, m_Bottom(height / 2)
{
	
}

void CollisionComponent::Update(GameContext&)
{
	
}

bool CollisionComponent::CheckCollision(const glm::vec2& position) const
{
	const auto pos = m_pTransform->GetAbsolutePosition();

	if (position.x < pos.x + m_Left)
		return false;

	if (position.x > pos.x + m_Right)
		return false;

	if (position.y < pos.y + m_Top)
		return false;

	if (position.y > pos.y + m_Bottom)
		return false;


	return true;
}

bool CollisionComponent::CollisionDetection(CollisionComponent* const pCollision) const
{
	if (pCollision->m_Left < m_Left)
		return false;

	if (pCollision->m_Right > m_Right)
		return false;

	if (pCollision->m_Top < m_Top)
		return false;

	if (pCollision->m_Bottom > m_Bottom)
		return false;

	return true;
}
