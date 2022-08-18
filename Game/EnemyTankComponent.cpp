#include "GamePCH.h"
#include "EnemyTankComponent.h"

#include "BulletConfigComponent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
#include "TransformComponent.h"
#include "Command.h"
#include "PlayerTankComponent.h"

EnemyTankComponent::EnemyTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, TankType tankType, int lives)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pMovement(pMovement)
	, m_pRender(pRender)
	, m_pCollision(pCollision)
	, m_Lives(lives)
	, m_Type(tankType)
{
	switch (m_Type)
	{
	case TankType::blueTank:
		m_pRender->SetSrcRect(SDL_Rect{ 00,96,32,32 });
		m_pMovement->SetMovementSpeed(125);
		break;
	case TankType::recognizer:
		m_pRender->SetSrcRect(SDL_Rect{ 64,64,32,32 });
		m_pMovement->SetMovementSpeed(250);
		break;
	}

	m_pRender->SetCenter({ 16,16 });
	m_pRender->SetPivot({ 16,16 });
}

EnemyTankComponent::~EnemyTankComponent()
{
	m_pTarget = nullptr;
}

void EnemyTankComponent::Update(GameContext&)
{
	MovementAI();
}

void EnemyTankComponent::SetTarget(GameObject* ptarget)
{
	m_pTarget = ptarget;

	m_pCollision->AddColliderCheck(
		m_pTarget->GetComponent<CollisionComponent>(), 
		new Command([this, ptarget]
		{
			ptarget->GetComponent<PlayerTankComponent>()->Kill();
			GetParent()->Remove();
		})
	);
}

void EnemyTankComponent::MovementAI() const
{
	static const float margin = 0.01f;
	// allows next frame to move
	m_pMovement->SetMoving(true);

	const glm::vec2& pos = m_pTransform->GetAbsolutePosition();
	const glm::vec2& targetPos = m_pTarget->GetComponent<TransformComponent>()->GetAbsolutePosition();
	glm::vec2 dir = normalize(targetPos - pos);

	// just in case the values are same, keep going in same direction
	if (fabs(dir.x) == fabs(dir.y))
		return;
	
	MovementComponent::Direction setDirTo{};
	if (fabs(dir.x) > fabs(dir.y)) // x is bigger than y
	{
		if (abs(dir.y) < margin)
		{
			if (dir.x < 0.f)	// target is left
				setDirTo = MovementComponent::Direction::left;
			else				// target is right
				setDirTo = MovementComponent::Direction::right;
		}
		else if (dir.y < 0.f) // target is above
		{
			setDirTo = MovementComponent::Direction::up;
		}
		else			// target is below
		{
			setDirTo = MovementComponent::Direction::down;
		}

		dir.y = 0.f;
	}
	else // y is bigger than x
	{
		if (abs(dir.x) < margin)
		{
			if (dir.y < 0.f)	// target is upwards
				setDirTo = MovementComponent::Direction::up;
			else				// target is downwards
				setDirTo = MovementComponent::Direction::down;
		}
		else if (dir.x < 0.f) // target is left
		{
			setDirTo = MovementComponent::Direction::left;
		}
		else			// target is right
		{
			setDirTo = MovementComponent::Direction::right;
		}

		dir.x = 0.f;
	}
	// ensures we get a unitvector direction
	dir = normalize(dir);

	m_pMovement->SetDirection(setDirTo);
	m_pRender->SetRotation(m_pMovement->GetDirectionVec());
}

void EnemyTankComponent::Hit()
{
	--m_Lives;
	if (m_Lives > 0)
		return;


	const auto pEnemy = GetParent();

	if (m_Type == TankType::blueTank)
		ServiceLocator::GetEventManager()->Notify(pEnemy, BlueTankDied);
	else if (m_Type == TankType::recognizer)
		ServiceLocator::GetEventManager()->Notify(pEnemy, RedRecognizerDied);

	pEnemy->Remove();
}
