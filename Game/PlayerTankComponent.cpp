#include "GamePCH.h"
#include "PlayerTankComponent.h"

#include "GameObject.h"
#include "MovementComponent.h"
#include "RenderComponent.h"

class CollisionComponent;
class LevelComponent;

PlayerTankComponent::PlayerTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement)
	: Component(pGo)
	, m_pRender(pRender)
	, m_pMovement(pMovement)
{
	m_pRender->SetSrcRect(SDL_Rect{ 00,64,32,32 });
	m_pRender->SetCenter({ 16,16 });
	m_pRender->SetPivot({ 16,16 });

	m_pMovement->SetMovementSpeed(125);
}

void PlayerTankComponent::MoveUp() const
{
	// the rotation values are already assigned to the enum values
	m_pRender->SetRotation(270);
	m_pMovement->SetDirection(MovementComponent::Direction::up);
}

void PlayerTankComponent::MoveDown() const
{
	m_pRender->SetRotation(90);
	m_pMovement->SetDirection(MovementComponent::Direction::down);
}

void PlayerTankComponent::MoveLeft() const
{
	m_pRender->SetRotation(180);
	m_pMovement->SetDirection(MovementComponent::Direction::left);
}

void PlayerTankComponent::MoveRight() const
{
	m_pRender->SetRotation(0);
	m_pMovement->SetDirection(MovementComponent::Direction::right);	
}



