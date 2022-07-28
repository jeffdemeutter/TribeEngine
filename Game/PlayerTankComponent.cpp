#include "GamePCH.h"
#include "PlayerTankComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include <CollisionComponent.h>
#include "Raycast.h"

class CollisionComponent;
class LevelComponent;

PlayerTankComponent::PlayerTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_pCollision(pCollision)
{
	m_pRender->SetSrcRect(SDL_Rect{ 00,64,32,32 });
	m_pRender->SetCenter({ 16,16 });
	m_pRender->SetPivot({ 16,16 });
}

PlayerTankComponent::~PlayerTankComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
	m_pCollision = nullptr;
}

void PlayerTankComponent::Update(GameContext& gc)
{
	DoMovement(gc);
}

void PlayerTankComponent::DoMovement(Movement movement)
{
	m_Movement = movement;
	m_IsMoving = true;

	// the rotation values are already assigned to the enum values
	m_pRender->SetRotation(float(movement));
}

void PlayerTankComponent::DoMovement(GameContext& gc)
{
	const auto& dTime = gc.pTime->GetDeltaTime();
	if (!m_IsMoving)
		return;

	auto& pos = m_pTransform->GetRelativePosition();
	glm::vec2 dir{};
	switch (m_Movement)
	{
	case Movement::up:
		dir = { 0, -1 };
		break;
	case Movement::right:
		dir = { 1, 0 };
		break;
	case Movement::down:
		dir = { 0, 1 };
		break;
	case Movement::left:
		dir = { -1, 0 };
		break;
	}
	pos += dir * m_MoveSpeed * dTime;


	const auto pLevelComp = gc.pSceneManager->GetActiveScene()->GetGameObjectByName("Level")->GetComponent<LevelComponent>();
	for (const auto& obstacle : pLevelComp->GetObstacles())
	{
		glm::vec2 start = obstacle.back();
		for (const auto& end : obstacle)
		{
			if (m_pCollision->CheckEdgeCollision(start, end))
			{
				pos -= dir * m_MoveSpeed * dTime * 2.f; // *2 to negate the movement its already done
				break;
			}
			start = end;
		}
	}

	m_IsMoving = false;
}
