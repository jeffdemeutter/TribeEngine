#include "GamePCH.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "TileComponent.h"

BulletComponent::BulletComponent(GameObject* pGo, TransformComponent* pTrans, const glm::vec2& direction, float speed)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_Speed(speed)
	, m_Direction(normalize(direction))
{
	
}

BulletComponent::~BulletComponent()
{
	m_pTransform = nullptr;
}

void BulletComponent::Update(GameContext& gc)
{
	m_Duration += gc.pTime->GetDeltaTime();
	if (m_Duration >= m_MaxDuration)
	{
		const auto pBulletObject = GetParent();
		pBulletObject->GetParent()->RemoveGameObject(pBulletObject);
	}

	auto& pos = m_pTransform->GetRelativePosition();

	//collision
	const auto pScene = gc.pSceneManager->GetActiveScene();
	const auto pLevel = pScene->GetGameObjectByName("Level")->GetComponent<LevelComponent>();
	
	for (const auto pTile : pLevel->GetNearbyTiles(m_pTransform->GetAbsolutePosition(), 30.f))
	{
		if (pTile->GetComponent<TileComponent>()->GetType() != TileType::wall)
			continue;

		const auto pCollision = pTile->GetComponent<CollisionComponent>();
		if (pCollision->CheckCollision(pos + m_Direction * m_Speed))
		{
			

		}
	}
}
