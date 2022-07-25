#include "GamePCH.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"

#include "Raycast.h"
#include "RenderComponent.h"

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
	const auto& dTime = gc.pTime->GetDeltaTime();
	m_Duration += dTime;
	if (m_Duration >= m_MaxDuration)
	{
		const auto pBulletObject = GetParent();
		pBulletObject->GetParent()->RemoveGameObject(pBulletObject);
	}

	auto& pos = m_pTransform->GetRelativePosition();

	const auto pLevelComp = gc.pSceneManager->GetActiveScene()->GetGameObjectByName("Level")->GetComponent<LevelComponent>();


	RaycastInfo rcInfo{};
	if (Raycast::DoRaycast(pos, m_Direction, m_Speed * dTime, pLevelComp->GetObstacles(), rcInfo))
	{
		m_Direction = rcInfo.reflect;
		pos = rcInfo.hitPos + m_Direction;
	}
	else
	{
		pos += m_Direction * m_Speed * gc.pTime->GetDeltaTime();
	}
}
