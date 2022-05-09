#include "TribePCH.h"
#include "PeterPepperComponent.h"

#include "SpriteAnimationComponent.h"
#include "EventManager.h"
#include "ServiceLocator.h"
#include "SoundManager.h"

enum SpriteActions
{
	idle,
	walkLeft,
	walkRight,
	climbUp,
	climbDown
};

PeterPepperComponent::PeterPepperComponent(GameObject* go, SpriteAnimationComponent* pAnim)
	: Component(go)
	, m_pAnimComponent(pAnim)
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

}

void PeterPepperComponent::DoDamage()
{
	m_Health -= 1;
	ServiceLocator::GetEventManager()->Notify(m_pParent, TookDamage);

	if (m_Health <= 0)
		ServiceLocator::GetEventManager()->Notify(m_pParent, PlayerDied);


	ServiceLocator::GetSoundManager()->QueueEffect(playerHit);
}

