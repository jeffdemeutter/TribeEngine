#include "GamePCH.h"
#include "BulletManagerComponent.h"

#include "BulletComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Command.h"

BulletManagerComponent::BulletManagerComponent(GameObject* pGo)
	: Component(pGo)
{
	
}

BulletManagerComponent::~BulletManagerComponent()
{
	for (auto pBullet : m_pBullets)
		pBullet = nullptr;
	m_pBullets.clear();

	for (auto [pCollision, pCommand] : m_pCollisions)
	{
		pCollision = nullptr;
		delete pCommand;
		pCommand = nullptr;
	}
	m_pCollisions.clear();
}

void BulletManagerComponent::Update(GameContext&)
{
	for (const auto [pCollision, pCommand] : m_pCollisions)
	{
		for (const auto pBullet : m_pBullets)
		{
			if (pCollision->CheckCollision(pBullet->GetAbsolutePosition()))
			{
				// remove the bullet
				GetParent()->RemoveGameObject(pBullet->GetParent());

				// run command
				pCommand->Execute();
			}
		}
	}
}

void BulletManagerComponent::AddCollision(CollisionComponent* pCollision, Command* pCommand)
{
	if (!pCollision)
		return;

	m_pCollisions.emplace_back(std::make_pair(pCollision, pCommand));
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

		m_pBullets.emplace_back(pTrans);
	}
}
