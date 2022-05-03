#include "TribePCH.h"
#include "PeterPepperComponent.h"

#include "EventManager.h"
#include "ServiceLocator.h"
#include "SoundManager.h"

PeterPepperComponent::PeterPepperComponent(GameObject* go)
	: Component(go)
{
	
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

