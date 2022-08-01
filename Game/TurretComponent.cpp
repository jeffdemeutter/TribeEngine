#include "GamePCH.h"
#include "TurretComponent.h"

#include "BulletComponent.h"
#include "BulletManagerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

TurretComponent::TurretComponent(GameObject* pGo, int player, TransformComponent* pTrans, RenderComponent* pRender)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_Player(player)
{
	m_pTransform->SetPosition(-9, -23);
	m_pRender->SetSrcRect(SDL_Rect{ 64,96,32,32 });
	m_pRender->SetPivot({ 9,23 });
}

TurretComponent::~TurretComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
}

void TurretComponent::SpawnBullet()
{
	const auto pTurret = GetParent();
	const auto pTank = static_cast<GameObject*>(pTurret->GetParent());
	const auto pScene = pTank->GetParent();

	const auto pBulletManager = pScene->GetGameObjectByName("BulletManager")->GetComponent<BulletManagerComponent>();
	pBulletManager->SpawnBullet(m_pTransform->GetAbsolutePosition() - glm::vec2{ -9, -23 }, m_Direction);
}

void TurretComponent::Update(GameContext& gc)
{
	if (m_Player == 0)
		m_Direction = gc.pInput->GetMousePosition() - m_pTransform->GetAbsolutePosition();
	else
	{
		m_Direction.x = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_LEFTX);
		m_Direction.y = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_LEFTY);
	}

	const float rotRad = atan2(-m_Direction.x, m_Direction.y);
	float rotDegrees = rotRad * 180 / gPI;
	rotDegrees += 90;

	m_pRender->SetRotation(rotDegrees);
}

