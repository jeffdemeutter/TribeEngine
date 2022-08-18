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

EnemyTankManager::EnemyTankManager(GameObject* pGo, GameObject* pTarget, LevelComponent* pLevel, BulletManagerComponent* pBulletManager)
	: Component(pGo)
	, m_pTarget(pTarget)
	, m_pLevel(pLevel)
	, m_pBulletManager(pBulletManager)
{
	ServiceLocator::GetEventManager()->AddEventHandle(ReloadScene, [this](GameObject*, int)
	{
		RespawnEnemies();
	});
}

void EnemyTankManager::Update(GameContext&)
{
	const size_t childCount = GetParent()->GetGameObjects().size();
	if (childCount <= 0)
		ServiceLocator::GetEventManager()->Notify(GetParent(), ReloadScene);
}

EnemyTankComponent* EnemyTankManager::AddEnemy(TankType type, bool initial)
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

			if (initial)
				++m_BlueTankCount;
		}
		else
		{
			pEnemyTank = pEnemy->AddComponent(new EnemyTankComponent(pEnemy, pTransform, pRender, pCollision, pMovement));

			if (initial)
				++m_RecognizerCount;
		}
		

		pMovement->SetLevelComponent(m_pLevel);
		pEnemyTank->SetTarget(m_pTarget);

		m_pBulletManager->AddCollision(pEnemy, new Command([pEnemyTank]
		{
			pEnemyTank->Hit();
		}));


		return pEnemyTank;
	}
}

void EnemyTankManager::RespawnEnemies()
{
	const auto pEnemyManager = GetParent();
	const auto& pEnemies = pEnemyManager->GetGameObjects();

	if (!pEnemies.empty())
	{
		for (GameObject* pEnemy : pEnemies)
			pEnemy->Remove();
	}
	else
	{
		for (int i = 0; i < m_BlueTankCount; ++i)
			AddEnemy(TankType::blueTank, false);


		for (int i = 0; i < m_RecognizerCount; ++i)
			AddEnemy(TankType::recognizer, false);
	}
}
