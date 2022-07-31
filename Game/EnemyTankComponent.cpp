#include "GamePCH.h"
#include "EnemyTankComponent.h"

#include "RenderComponent.h"
#include "MovementComponent.h"

EnemyTankComponent::EnemyTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement, TankType tankType)
		: TankComponent(pGo, pRender, pMovement)
{
	switch (tankType)
	{
	case TankType::blueTank:
		m_pRender->SetSrcRect(SDL_Rect{ 00,96,32,32 });
		m_pMovement->SetMovementSpeed(125);
		break;
	case TankType::recognizer:
		m_pRender->SetSrcRect(SDL_Rect{ 64,64,32,32 });
		m_pMovement->SetMovementSpeed(250);
		break;
	}

	m_pRender->SetCenter({ 16,16 });
	m_pRender->SetPivot({ 16,16 });
}

EnemyTankComponent::~EnemyTankComponent()
{
	m_pTarget = nullptr;
}

void EnemyTankComponent::MovementAI()
{
	
}
