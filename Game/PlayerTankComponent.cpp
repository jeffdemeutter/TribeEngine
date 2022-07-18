#include "GamePCH.h"
#include "PlayerTankComponent.h"

#include "GameTime.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "SpriteAnimationComponent.h"

PlayerTankComponent::PlayerTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
{
	m_pRender->SetSrcRect(SDL_Rect{ 00,64,32,32 });

	m_pRender->SetCenter({ 16, 16 });
	m_pRender->SetPivot({ 16,16 });
}

PlayerTankComponent::~PlayerTankComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
}

void PlayerTankComponent::Update(GameContext& gc)
{
	if (!m_IsMoving)
		return;

	auto& pos = m_pTransform->GetPosition();
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

void PlayerTankComponent::DoMovement(Movement movement)
{
	m_Movement = movement;
	m_IsMoving = true;

	// the rotation values are already assigned to the enum values
	m_pRender->SetRotation(float(movement));
}
