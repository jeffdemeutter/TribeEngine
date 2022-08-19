#include "GamePCH.h"
#include "TurretComponent.h"

#include "BulletComponent.h"
#include "BulletConfigComponent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "SoundManager.h"

TurretComponent::TurretComponent(GameObject* pGo, int player, TransformComponent* pTrans, RenderComponent* pRender, BulletConfigComponent* pBulletConfig)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_pBulletConfig(pBulletConfig)
	, m_Player(player)
{
	m_pTransform->SetPosition(-9, -23);
	m_pRender->SetSrcRect(SDL_Rect{ 64,96,32,32 });
	m_pRender->SetPivot({ 9,23 });

	m_pBulletConfig->SetSpeed(300.f);
	m_pBulletConfig->SetPivot({3.f, 2.5f});
	m_pBulletConfig->SetSrcRect(SDL_Rect{ 109, 46, 6, 5 });
	// first getparent is turret, second is the tank
	m_pBulletConfig->SetSourceObject(static_cast<GameObject*>(GetParent()->GetParent()));
}

TurretComponent::~TurretComponent()
{
	m_pTransform = nullptr;
	m_pRender = nullptr;
}

void TurretComponent::SpawnBullet() const
{
	if (!GetParent()->IsActive())
		return;

	m_pBulletConfig->SetPos(m_pTransform->GetAbsolutePosition() - glm::vec2{ -9, -23 });
	m_pBulletConfig->SetDirection(m_Direction);


	ServiceLocator::GetEventManager()->Notify(GetParent(), PlayerSpawnedBullet);
	ServiceLocator::GetSoundManager()->QueueEffect(shot);
}

void TurretComponent::Update(GameContext& gc)
{
	if (m_Player == 0)
	{
		if (gc.pInput->IsControllerConnected())
		{
			glm::vec2 controllerPos = {gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_RIGHTX), gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_RIGHTY)};
			if (length(controllerPos) >= 0.4f)
			{
				m_Direction = controllerPos;
			}
		}
		else
		{
			m_Direction = InputManager::GetMousePosition() - m_pTransform->GetAbsolutePosition();
		}
	}
	else
	{
		m_Direction.x = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_RIGHTX);
		m_Direction.y = gc.pInput->GetJoystickAxis(m_Player, SDL_CONTROLLER_AXIS_RIGHTY);
	}

	const float rotRad = atan2(-m_Direction.x, m_Direction.y);
	float rotDegrees = rotRad * 180 / gPI;
	rotDegrees += 90;

	m_pRender->SetRotation(rotDegrees);
}

