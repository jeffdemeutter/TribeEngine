#include "GamePCH.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"

#include "Raycast.h"

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
		SetCanBeDestroyed();

	auto& pos = m_pTransform->GetRelativePosition();

	const auto pLevelComp = gc.pSceneManager->GetActiveScene()->GetGameObjectByName("Level")->GetComponent<LevelComponent>();

	
	if (RaycastInfo rcInfo{}; Raycast::DoRaycast(pos, m_Direction, m_Speed * dTime, pLevelComp->GetObstacles(), rcInfo))
	{
		++m_Bounces;
		if (m_Bounces > m_BouncesMax)
			SetCanBeDestroyed();

		m_Direction = rcInfo.reflect;
		pos = rcInfo.hitPos + m_Direction;
	}
	else
		pos += m_Direction * m_Speed * gc.pTime->GetDeltaTime();
}