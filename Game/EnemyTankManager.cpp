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
#include "ServiceLocator.h"
#include "EventManager.h"

EnemyTankManager::EnemyTankManager(GameObject* pGo, LevelComponent* pLevel, BulletManagerComponent* pBulletManager)
	: Component(pGo)
	, m_EnemyCountType1(0)
	, m_EnemyCountType2(0)
	, m_pLevel(pLevel)
	, m_pBulletManager(pBulletManager)
{
	ServiceLocator::GetEventManager()->AddEventHandle(PlayerDied, [this](GameObject* pGo, int)
	{
		RespawnEnemies(pGo);
	});
	
}

EnemyTankComponent* EnemyTankManager::AddEnemy(TankType type, bool initialSpawn)
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

			if(initialSpawn)
				m_EnemyCountType1++;
		}
		else
		{
			pEnemyTank = pEnemy->AddComponent(new EnemyTankComponent(pEnemy, pTransform, pRender, pCollision, pMovement));

			if (initialSpawn)
				m_EnemyCountType2++;
		}

		pMovement->SetLevelComponent(m_pLevel);


		m_pBulletManager->AddCollision(pEnemy, new Command([pEnemyTank]
		{
			pEnemyTank->Hit();
		}));


		return pEnemyTank;
	}
}

void EnemyTankManager::RespawnEnemies(GameObject* pPlayerTarget)
{
	const auto& objects = GetParent()->GetGameObjects();
	for (GameObject* element : objects)
		element->Remove();

	for (int i = 0; i < m_EnemyCountType1; ++i)
	{
		const auto pEnemy = AddEnemy(TankType::blueTank, false);
		pEnemy->SetTarget(pPlayerTarget);
	}

	for (int i = 0; i < m_EnemyCountType2; ++i)
	{
		const auto pEnemy = AddEnemy(TankType::recognizer, false);
		pEnemy->SetTarget(pPlayerTarget);
	}
}
