#include "GamePCH.h"
#include "TurretComponent.h"

#include "BulletComponent.h"
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
	m_pRender->SetSrcRect(SDL_Rect{ 64,96,32,32 });
	m_pRender->SetCenter({ 9,23 });
	m_pRender->SetPivot({ 9,23 });
}

TurretComponent::~TurretComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
}

void TurretComponent::SpawnBullet()
{
	const auto& pTurret = GetParent();
	const auto& pTank = static_cast<GameObject*>(pTurret->GetParent());
	const auto& pScene = pTank->GetParent();


	const auto pBullet = pScene->AddGameObject("Bullet");
	{
		const auto pTrans = pBullet->AddComponent(new TransformComponent(pBullet, m_pTransform->GetAbsolutePosition()));
		const auto pRender = pBullet->AddComponent(new RenderComponent(pBullet, pTrans, "spritesheet.png"));
		pRender->SetSrcRect({ 96, 32, 32, 32 });
		pBullet->AddComponent(new BulletComponent(pBullet, pTrans));
	}
}

void TurretComponent::Update(GameContext& gc)
{
	glm::vec2 dir;
	if (m_Player == 0)
		dir = gc.pInput->GetMousePosition() - m_pTransform->GetAbsolutePosition();
	else
	{
		dir.x = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_LEFTX);
		dir.y = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_LEFTY);
	}

	const float rotRad = atan2(-dir.x, dir.y);
	float rotDegrees = rotRad * 180 / gPI;
	rotDegrees += 90;

	m_pRender->SetRotation(rotDegrees);
}

