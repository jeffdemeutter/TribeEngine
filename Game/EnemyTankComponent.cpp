#include "GamePCH.h"
#include "EnemyTankComponent.h"

#include "EventManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "ServiceLocator.h"

EnemyTankComponent::EnemyTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement, TankType tankType)
	: TankComponent(pGo, pRender, pMovement)
	, m_Type(tankType)
{
	switch (m_Type)
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

void EnemyTankComponent::Kill() const
{
	const auto pTank = GetParent();

	if (m_Type == TankType::blueTank)
		ServiceLocator::GetEventManager()->Notify(pTank, BlueTankDied);
	else if (m_Type == TankType::recognizer)
		ServiceLocator::GetEventManager()->Notify(pTank, RedRecognizerDied);

	pTank->Remove();
}
