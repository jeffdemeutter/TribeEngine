#include "GamePCH.h"
#include "LivesComponent.h"

#include "EventManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

LivesComponent::LivesComponent(GameObject* pGo, TextComponent* pText, int lives)
	: Component(pGo)
	, m_Lives(lives)
	, m_pTextComponent(pText)
{
	ServiceLocator::GetEventManager()->AddEventHandle(PlayerDied, [this](GameObject*, int) { DecreaseLive(); });

	m_pTextComponent->SetBackgroundColor(SDL_Color{ 0,0,0,255 });
	m_pTextComponent->SetText("HHH");
}

void LivesComponent::DecreaseLive()
{
	--m_Lives;

	if (m_Lives == 0)
		ServiceLocator::GetEventManager()->Notify(GetParent(), GameOver);
}


