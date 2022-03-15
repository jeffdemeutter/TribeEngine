#include "TribePCH.h"
#include "DeadSignComponent.h"

#include "TextComponent.h"
#include "EventManager.h"

DeadSignComponent::DeadSignComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{
	EventManager::AddEventHandle(PlayerDied, [this](GameObject* go) {this->NotifyDead(go); });
}
void DeadSignComponent::NotifyDead(GameObject*)
{
	m_pTextComponent->SetVisibility(true);
}
