#include "GamePCH.h"
#include "TankComponent.h"

#include "RenderComponent.h"
#include "MovementComponent.h"

TankComponent::TankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement)
	: Component(pGo)
	, m_pRender(pRender)
	, m_pMovement(pMovement)
{

}

TankComponent::~TankComponent()
{
	m_pRender = nullptr;
	m_pMovement = nullptr;
} 
