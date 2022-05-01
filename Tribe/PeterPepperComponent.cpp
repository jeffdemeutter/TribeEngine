#include "TribePCH.h"
#include "PeterPepperComponent.h"

#include "EventManager.h"
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
	EventManager::Notify(m_pParent, TookDamage);

	if (m_Health <= 0)
		EventManager::Notify(m_pParent, PlayerDied);

	SoundManager::PlayEffect(playerHit);
}

