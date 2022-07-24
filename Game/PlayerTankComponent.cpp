#include "GamePCH.h"
#include "PlayerTankComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

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
}

void PlayerTankComponent::Update(GameContext& gc)
{
	DoMovement(gc);


	// check collision
	//const auto activeScene = gc.pSceneManager->GetActiveScene();
	//const auto pLevel = activeScene->GetGameObjectByName("Level")->GetComponent<LevelComponent>();

	//const auto nearbyTiles = pLevel->GetNearbyTiles(m_pTransform->GetAbsolutePosition(), 30.f);


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
	if (!m_IsMoving)
		return;

	auto& pos = m_pTransform->GetRelativePosition();
	switch (m_Movement)
	{
	case Movement::up:
		pos.y -= m_MoveSpeed * gc.pTime->GetDeltaTime();
		break;
	case Movement::right:
		pos.x += m_MoveSpeed * gc.pTime->GetDeltaTime();
		break;
	case Movement::down:
		pos.y += m_MoveSpeed * gc.pTime->GetDeltaTime();
		break;
	case Movement::left:
		pos.x -= m_MoveSpeed * gc.pTime->GetDeltaTime();
		break;
	}

	m_IsMoving = false;
}
