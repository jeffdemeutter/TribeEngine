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

BulletManagerComponent::BulletManagerComponent(GameObject* pGo)
	: Component(pGo)
{
	ServiceLocator::GetEventManager()->AddEventHandle(GameobjectDeleted, [this](GameObject* pObj, int) { 	RemoveCollision(pObj); });

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

void BulletManagerComponent::SpawnBullet(const glm::vec2& pos, const glm::vec2& dir)
{
	const auto pBullet = GetParent()->AddGameObject("Bullet");
	{
		const auto pTrans = pBullet->AddComponent(new TransformComponent(pBullet));
		const auto pRender = pBullet->AddComponent(new RenderComponent(pBullet, pTrans, "spritesheet.png"));
		pBullet->AddComponent(new BulletComponent(pBullet, pTrans, dir, 300.f));

		pTrans->SetPosition(pos);

		pRender->SetSrcRect({ 109, 46, 6, 5 });
		pRender->SetPivot({ 3.f, 2.5f });

	}
	m_pBullets.emplace_back(pBullet);
}
