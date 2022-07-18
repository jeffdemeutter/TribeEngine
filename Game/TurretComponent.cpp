#include "GamePCH.h"
#include "TurretComponent.h"

#include "InputManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

TurretComponent::TurretComponent(GameObject* pGo, int player, TransformComponent* pTrans, RenderComponent* pRender)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_Player(player)
{
	
}

TurretComponent::~TurretComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
}

void TurretComponent::Update(GameContext& gc)
{
	const auto dir = gc.pInput->GetMousePosition() - m_pTransform->GetPosition();
	
	const float rotRad = atan2(-dir.x, dir.y);
	const float rotDegrees = rotRad * 180 / gPI;

	m_pRender->SetRotation(rotDegrees);
}

