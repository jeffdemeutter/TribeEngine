#include "TribePCH.h"
#include "PeterPepperComponent.h"

#include "RenderComponent.h"
#include "EventManager.h"
#include "ServiceLocator.h"
#include "SoundManager.h"

PeterPepperComponent::PeterPepperComponent(GameObject* go, RenderComponent* pRender)
	: Component(go)
{
	pRender->SetSrcRect({ 16, 0, 16, 16 });



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

