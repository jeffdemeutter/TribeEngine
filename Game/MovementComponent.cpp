#include "GamePCH.h"
#include "MovementComponent.h"

#include "GameTime.h"
#include "LevelComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"

MovementComponent::MovementComponent(GameObject* pGo, TransformComponent* pTrans, CollisionComponent* pCollision)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pCollision(pCollision)
{
	
}

MovementComponent::~MovementComponent()
{
	m_pLevel = nullptr;
	m_pTransform = nullptr;
	m_pCollision = nullptr;
}

void MovementComponent::Update(GameContext& gc)
{
	const auto& dTime = gc.pTime->GetDeltaTime();
	if (!m_IsMoving)
		return;

	auto& pos = m_pTransform->GetRelativePosition();
	glm::vec2 dir{};
	switch (m_Movement)
	{
	case Movement::up:
		dir = { 0, -1 };
		break;
	case Movement::right:
		dir = { 1, 0 };
		break;
	case Movement::down:
		dir = { 0, 1 };
		break;
	case Movement::left:
		dir = { -1, 0 };
		break;
	}
	pos += dir * m_MoveSpeed * dTime;


	bool edgeCollision = false;
	for (const auto& obstacle : m_pLevel->GetObstacles())
	{
		glm::vec2 start = obstacle.back();
		for (const auto& end : obstacle)
		{
			if (m_pCollision->CheckEdgeCollision(start, end))
			{
				pos -= dir * m_MoveSpeed * dTime * 2.f; // *2 to negate the movement its already done
				edgeCollision = true;
				break;
			}
			start = end;
		}
		if (edgeCollision)
			break;
	}

	m_IsMoving = false;
}

void MovementComponent::SetMovement(Movement movement)
{
	m_Movement = movement;
	m_IsMoving = true;
}
