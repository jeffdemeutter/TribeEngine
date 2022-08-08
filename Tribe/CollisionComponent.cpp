#include "TribePCH.h"
#include "CollisionComponent.h"

#include "Command.h"
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

CollisionComponent::~CollisionComponent()
{
	for (auto& [pCollider, pCommand] : m_pCollideChecks)
	{
		pCollider = nullptr;
		SafeDelete(pCommand);
	}
	m_pCollideChecks.clear();

	m_pTransform = nullptr;
}


void CollisionComponent::Update(GameContext&)
{
	for (const auto& [pCollision, pCommand] : m_pCollideChecks)
		if (pCollision->IsOverlapping(this))
			pCommand->Execute();
}

void CollisionComponent::AddColliderCheck(CollisionComponent* pCollision, Command* pCommand)
{
	if (!pCollision)
		return;

	if (!pCommand)
		return;


	m_pCollideChecks.emplace_back(std::make_pair(pCollision, pCommand));
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

bool CollisionComponent::CheckEdgeCollision(const glm::vec2& p1, const glm::vec2& p2) const
{
	const auto pos = m_pTransform->GetAbsolutePosition();

	if (p1.x < pos.x + m_Left && p2.x < pos.x + m_Left)
		return false;

	if (p1.x > pos.x + m_Right && p2.x > pos.x + m_Right)
		return false;

	if (p1.y < pos.y + m_Top && p2.y < pos.y + m_Top)
		return false;

	if (p1.y > pos.y + m_Bottom && p2.y > pos.y + m_Bottom)
		return false;

	return true;
}

bool CollisionComponent::IsOverlapping(CollisionComponent* pCollision) const
{
	const auto otherPos = pCollision->m_pTransform->GetAbsolutePosition();
	const auto pos = m_pTransform->GetAbsolutePosition();

	if (otherPos.x + pCollision->m_Right	< pos.x + m_Left)
		return false;

	if (otherPos.x + pCollision->m_Left		> pos.x + m_Right)
		return false;

	if (otherPos.y + pCollision->m_Bottom	< pos.y + m_Top)
		return false;

	if (otherPos.y + pCollision->m_Top		> pos.y + m_Bottom)
		return false;

	return true;
}

glm::vec2 CollisionComponent::GetCornerPos(corners corner)
{
	glm::vec2 cornerPos = m_pTransform->GetAbsolutePosition();
	switch (corner) {
	case topLeft:
		cornerPos.x += m_Left;
		cornerPos.y += m_Top;
		break;
	case topRight:
		cornerPos.x += m_Right;
		cornerPos.y += m_Top;
		break;
	case bottomLeft:
		cornerPos.x += m_Left;
		cornerPos.y += m_Bottom;
		break;
	case bottomRight:
		cornerPos.x += m_Right;
		cornerPos.y += m_Bottom;
		break;
	}

	return cornerPos;
}
