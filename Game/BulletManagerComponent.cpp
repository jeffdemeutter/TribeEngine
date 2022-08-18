#include "GamePCH.h"
#include "BulletManagerComponent.h"

#include "BulletComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Command.h"
#include "EventManager.h"
#include "ServiceLocator.h"
#include "BulletConfigComponent.h"

BulletManagerComponent::BulletManagerComponent(GameObject* pGo, LevelComponent* pLevelComp)
	: Component(pGo)
	, m_pLevelComponent(pLevelComp)
{
	ServiceLocator::GetEventManager()->AddEventHandle(GameobjectDeleted, [this](GameObject* pObj, int)
	{
		RemoveCollision(pObj);
	});


	const auto spawnBulletLambda = [this](GameObject* pObj, int)
	{
		SpawnBullet(pObj->GetComponent<BulletConfigComponent>());
	};
	ServiceLocator::GetEventManager()->AddEventHandle(EnemySpawnedBullet, spawnBulletLambda);
	ServiceLocator::GetEventManager()->AddEventHandle(PlayerSpawnedBullet, spawnBulletLambda);


}

BulletManagerComponent::~BulletManagerComponent()
{
	m_pBullets.clear();

	for (auto& [pGo, pCommand] : m_pGameObjects)
	{
		SafeDelete(pCommand);
	}
	m_pGameObjects.clear();
}

void BulletManagerComponent::Update(GameContext&)
{
	if (m_pGameObjects.empty())
		return;

	for (auto pBullet : m_pBullets)
	{
		const auto pTrans = pBullet->GetComponent<TransformComponent>();
		const auto pBulletComp = pBullet->GetComponent<BulletComponent>();
		for (const auto& pGo : m_pGameObjects)
		{
			if (pBulletComp->GetOriginFired() == pGo.first)
				continue;

			if (pGo.first->GetComponent<CollisionComponent>()->CheckCollision(pTrans->GetAbsolutePosition()))
			{
				pBulletComp->SetCanBeDestroyed();

				// run command
				pGo.second->Execute();
			}			
		}

		// remove the bullet
		if (pBulletComp->CanBeDestroyed())
		{
			pBullet->Remove();
			m_pBullets.erase(std::ranges::find(m_pBullets, pBullet));
		}
	}
}

void BulletManagerComponent::AddCollision(GameObject* pGo, Command* pCommand)
{
	if (!pGo)
		return;

	m_pGameObjects[pGo] = pCommand;
}

void BulletManagerComponent::RemoveCollision(GameObject* pGo)
{
	if (!m_pGameObjects.contains(pGo))
		return;

	SafeDelete(m_pGameObjects.at(pGo));
	m_pGameObjects.erase(pGo);	
}


void BulletManagerComponent::SpawnBullet(BulletConfigComponent* pBulletConfig)
{
	const auto& srcRect = pBulletConfig->GetSrcRect();
	const auto& dir = pBulletConfig->GetDirection();
	const auto& pos = pBulletConfig->GetPos();
	const auto& pivot = pBulletConfig->GetPivot();
	const auto& speed	 = pBulletConfig->GetSpeed();
	const auto pSource = pBulletConfig->GetSourceObject();

	// spawn the bullet
	const auto pBullet = GetParent()->AddGameObject("Bullet");
	{
		const auto pTrans = pBullet->AddComponent(new TransformComponent(pBullet));
		const auto pRender = pBullet->AddComponent(new RenderComponent(pBullet, pTrans, "spritesheet.png"));
		pBullet->AddComponent(new BulletComponent(pBullet, pTrans, m_pLevelComponent, dir, speed, pSource));

		pTrans->SetPosition(pos);

		pRender->SetSrcRect(srcRect);
		pRender->SetPivot(pivot);
	}
	m_pBullets.emplace_back(pBullet);
}
