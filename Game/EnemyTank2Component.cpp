#include "GamePCH.h"
#include "EnemyTank2Component.h"
#include "BulletConfigComponent.h"
#include "ServiceLocator.h"
#include "GameTime.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "EventManager.h"

EnemyTank2Component::EnemyTank2Component(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender,
										 CollisionComponent* pCollision, MovementComponent* pMovement, BulletConfigComponent* pBulletConfig, LevelComponent* pLevel)
	: EnemyTankComponent(pGo, pTrans, pRender, pCollision, pMovement, pLevel, TankType::blueTank)
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
}
