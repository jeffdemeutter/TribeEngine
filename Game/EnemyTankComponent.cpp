#include "GamePCH.h"
#include "EnemyTankComponent.h"

#include "BulletConfigComponent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "TransformComponent.h"
#include "Raycast.h"
#include "LevelComponent.h"

EnemyTankComponent::EnemyTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, BulletConfigComponent* pBulletConfig, LevelComponent* pLevel, TankType tankType, int lives)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_pCollision(pCollision)
	, m_pMovement(pMovement)
	, m_pBulletConfig(pBulletConfig)
	, m_pLevel(pLevel)
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


	m_pBulletConfig->SetSrcRect(SDL_Rect{ 11, 44, 8, 9 });
	m_pBulletConfig->SetPivot({ 4.f, 4.5f });
	m_pBulletConfig->SetSpeed(200.f);

	m_pBulletConfig->SetSourceObject(GetParent());
}

EnemyTankComponent::~EnemyTankComponent()
{
	m_pTarget = nullptr;
}

void EnemyTankComponent::Update(GameContext& gc)
{
	m_Timer += gc.pTime->GetDeltaTime();
	if (m_CanShoot)
	{
		if (m_Timer > m_TimerMax)
		{
			m_pBulletConfig->SetPos(m_pTransform->GetAbsolutePosition());
			m_pBulletConfig->SetDirection(m_pMovement->GetDirectionVec());

			ServiceLocator::GetEventManager()->Notify(GetParent(), EnemySpawnedBullet);
			m_Timer = 0;
		}
	}

	MovementAI();
}

void EnemyTankComponent::MovementAI()
{
	static float margin = 0.01f;
	// allows next frame to move
	m_pMovement->SetMoving(true);

	const glm::vec2& pos = m_pTransform->GetAbsolutePosition();
	const glm::vec2& targetPos = m_pTarget->GetComponent<TransformComponent>()->GetAbsolutePosition();
	glm::vec2 dir = normalize(targetPos - pos);

	// just in case the values are same, keep going in same direction
	if (fabs(dir.x) == fabs(dir.y))
		return;

	glm::vec2 cornerPos{};
	MovementComponent::Direction setDirTo{};
	if (fabs(dir.x) > fabs(dir.y)) // x is bigger than y
	{
		if (abs(dir.y) < margin)
		{
			if (dir.x < 0.f)	// target is left
				setDirTo = MovementComponent::Direction::left;
			else				// target is right
				setDirTo = MovementComponent::Direction::right;
			m_CanShoot = true;
		}
		else if (dir.y < 0.f) // target is above
		{
			if (dir.x < 0.f)	// target is left
				cornerPos = m_pCollision->GetCornerPos(topLeft);
			else				// target is right
				cornerPos = m_pCollision->GetCornerPos(topRight);

			setDirTo = MovementComponent::Direction::up;
			m_CanShoot = false;
		}
		else			// target is below
		{
			if (dir.x < 0.f)	// target is left
				cornerPos = m_pCollision->GetCornerPos(bottomLeft);
			else				// target is right
				cornerPos = m_pCollision->GetCornerPos(bottomRight);

			setDirTo = MovementComponent::Direction::down;
			m_CanShoot = false;
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
			m_CanShoot = true;
		}
		else if (dir.x < 0.f) // target is left
		{
			if (dir.y < 0.f)	// target is upwards
				cornerPos = m_pCollision->GetCornerPos(bottomLeft);
			else				// target is downwards
				cornerPos = m_pCollision->GetCornerPos(topLeft);

			setDirTo = MovementComponent::Direction::left;
			m_CanShoot = false;
		}
		else			// target is right
		{
			if (dir.y < 0.f)	// target is upwards
				cornerPos = m_pCollision->GetCornerPos(bottomRight);
			else				// target is downwards
				cornerPos = m_pCollision->GetCornerPos(topRight);

			setDirTo = MovementComponent::Direction::right;
			m_CanShoot = false;
		}

		dir.x = 0.f;
	}
	// ensures we get a unitvector direction
	dir = normalize(dir);

	RaycastInfo rcInfo{};
	if (Raycast::DoRaycast(cornerPos, dir, 40, m_pLevel->GetObstacles(), rcInfo))
		return;

	m_pMovement->SetDirection(setDirTo);
}

void EnemyTankComponent::Hit()
{
	--m_Lives;
	if (m_Lives > 0)
		return;

	

	const auto pTank = GetParent();

	if (m_Type == TankType::blueTank)
		ServiceLocator::GetEventManager()->Notify(pTank, BlueTankDied);
	else if (m_Type == TankType::recognizer)
		ServiceLocator::GetEventManager()->Notify(pTank, RedRecognizerDied);

	pTank->Remove();
}
