#include "GamePCH.h"
#include "EnemyTankManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "BulletConfigComponent.h"
#include "Command.h"
#include "LevelComponent.h"
#include "EnemyTank2Component.h"
#include "BulletManagerComponent.h"

EnemyTankManager::EnemyTankManager(GameObject* pGo, LevelComponent* pLevel, BulletManagerComponent* pBulletManager)
	: Component(pGo)
	, m_pLevel(pLevel)
	, m_pBulletManager(pBulletManager)
{
	
}

EnemyTankComponent* EnemyTankManager::AddEnemy(TankType type)
{
	const auto pEnemy = GetParent()->AddGameObject("enemy");
	{
		const auto pTransform = pEnemy->AddComponent(new TransformComponent(pEnemy, m_pLevel->GetRandomPosition()));
		const auto pRender = pEnemy->AddComponent(new RenderComponent(pEnemy, pTransform, "spritesheet.png"));
		const auto pCollision = pEnemy->AddComponent(new CollisionComponent(pEnemy, pTransform, 25, 25));
		const auto pMovement = pEnemy->AddComponent(new MovementComponent(pEnemy, pTransform, pCollision));

		EnemyTankComponent* pEnemyTank;
		if (type == TankType::blueTank)
		{
			const auto pBulletConfig = pEnemy->AddComponent(new BulletConfigComponent(pEnemy));
			pEnemyTank = pEnemy->AddComponent(new EnemyTank2Component(pEnemy, pTransform, pRender, pCollision, pMovement, pBulletConfig));
		}
		else
			pEnemyTank = pEnemy->AddComponent(new EnemyTankComponent(pEnemy, pTransform, pRender, pCollision, pMovement));

		pMovement->SetLevelComponent(m_pLevel);


		m_pBulletManager->AddCollision(pEnemy, new Command([pEnemyTank]
		{
			pEnemyTank->Hit();
		}));


		return pEnemyTank;
	}
}
