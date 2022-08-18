#include "GamePCH.h"
#include "EnemyTank2Component.h"
#include "BulletConfigComponent.h"
#include "ServiceLocator.h"
#include "GameTime.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "EventManager.h"
#include "GameObject.h"

EnemyTank2Component::EnemyTank2Component(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender,
										 CollisionComponent* pCollision, MovementComponent* pMovement, BulletConfigComponent* pBulletConfig)
	: EnemyTankComponent(pGo, pTrans, pRender, pCollision, pMovement, TankType::blueTank)
	, m_pBulletConfig(pBulletConfig)
{
	m_pBulletConfig->SetSrcRect(SDL_Rect{ 11, 44, 8, 9 });
	m_pBulletConfig->SetPivot({ 4.f, 4.5f });
	m_pBulletConfig->SetSpeed(200.f);

	m_pBulletConfig->SetSourceObject(GetParent());
}

void EnemyTank2Component::Update(GameContext& gameContext)
{
	EnemyTankComponent::Update(gameContext);

	m_Timer += gameContext.pTime->GetDeltaTime();
	if (m_Timer > m_TimerMax)
	{
		if (CanShoot())
		{
			m_pBulletConfig->SetPos(m_pTransform->GetAbsolutePosition());
			m_pBulletConfig->SetDirection(m_pMovement->GetDirectionVec());

			ServiceLocator::GetEventManager()->Notify(GetParent(), EnemySpawnedBullet);
			m_Timer = 0;
		}
	}
}

bool EnemyTank2Component::CanShoot() const
{
	const glm::vec2& pos = m_pTransform->GetAbsolutePosition();
	const glm::vec2& targetPos = m_pTarget->GetComponent<TransformComponent>()->GetAbsolutePosition();
	
	if (abs(pos.x - targetPos.x) < 5.f)
		return true;

	if (abs(pos.y - targetPos.y) < 5.f)
		return true;


	return false;
}
