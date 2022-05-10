#include "TribePCH.h"
#include "PeterPepperComponent.h"

#include "TransformComponent.h"
#include "SpriteAnimationComponent.h"
#include "EventManager.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "Timer.h"


PeterPepperComponent::PeterPepperComponent(GameObject* go, TransformComponent* pTrans, SpriteAnimationComponent* pAnim)
	: Component(go)
	, m_pAnimComponent(pAnim)
	, m_pTransformComponent(pTrans)
{
	m_pAnimComponent->AddAnimation(idle		, { 16 , 0, 16, 16 }, 16, 1);
	m_pAnimComponent->AddAnimation(walkLeft , { 48 , 0, 48, 16 }, 16, 3);
	m_pAnimComponent->AddAnimation(walkRight, { 144, 0, 48, 16 }, 16, 3);
	m_pAnimComponent->AddAnimation(climbUp	, { 96 , 0, 48, 16 }, 16, 3);
	m_pAnimComponent->AddAnimation(climbDown, { 0  , 0, 48, 16 }, 16, 3);
	

	m_pAnimComponent->SetActiveAnimation(idle);
}

PeterPepperComponent::~PeterPepperComponent()
{
	m_pAnimComponent = nullptr;
}

void PeterPepperComponent::Update()
{
	DoMovement();
}

void PeterPepperComponent::TakeDamage()
{
	m_Health -= 1;
	ServiceLocator::GetEventManager()->Notify(m_pParent, TookDamage);

	if (m_Health <= 0)
		ServiceLocator::GetEventManager()->Notify(m_pParent, PlayerDied);


	ServiceLocator::GetSoundManager()->QueueEffect(playerHit);
}

void PeterPepperComponent::DoMovement() const
{
	if (m_ActiveMovement == idle)
		return;

	const float dTime = Timer::GetDeltaTime();
	auto pos = m_pTransformComponent->GetPosition(); // intentional copy

	switch (m_ActiveMovement)
	{
	case walkLeft:
		pos.x -= m_MovementSpeed * dTime;
		break;
	case walkRight:
		pos.x += m_MovementSpeed * dTime;
		break;
	case climbUp:
		pos.y -= m_MovementSpeed * dTime;
		break;
	case climbDown:
		pos.y += m_MovementSpeed * dTime;
		break;
	}
	m_pAnimComponent->SetActiveAnimation(m_ActiveMovement);
	m_pTransformComponent->SetPosition(pos);
}
