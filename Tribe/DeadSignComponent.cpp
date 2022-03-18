#include "TribePCH.h"
#include "DeadSignComponent.h"

#include "TextComponent.h"

DeadSignComponent::DeadSignComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{
	EventManager::AddEventHandle(PlayerDied, [this](GameObject* go, EventType type) {this->NotifyDead(go, type); });
}
void DeadSignComponent::NotifyDead(GameObject*, EventType)
{
	m_pTextComponent->SetVisibility(true);
}
