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
	m_pTextComponent->SetText("XXX");
}

void LivesComponent::DecreaseLive()
{
	if (m_Lives > 0)
	{
		--m_Lives;
		ServiceLocator::GetEventManager()->Notify(GetParent(), ReloadScene);		
	}

	if (m_Lives == 0)
	{
		m_pTextComponent->SetText(" ");
		ServiceLocator::GetEventManager()->Notify(GetParent(), GameOver);
		return;
	}

	std::stringstream ss{};
	for (int i = 0; i < m_Lives; ++i)
		ss << 'X';
	m_pTextComponent->SetText(ss.str());

}


