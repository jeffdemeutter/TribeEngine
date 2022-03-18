#include "TribePCH.h"
#include "RemainingLivesComponent.h"

#include "TextComponent.h"
#include "PeterPepperComponent.h"

RemainingLivesComponent::RemainingLivesComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{


	EventManager::AddEventHandle(TookDamage, [this](GameObject* go, EventType type) {this->UpdateLives(go, type); });
}

RemainingLivesComponent::~RemainingLivesComponent()
{
	m_pTextComponent = nullptr;
}

void RemainingLivesComponent::UpdateLives(GameObject* go, EventType) const
{
	auto pPeter = go->GetComponent<PeterPepperComponent>();
	m_pTextComponent->SetText(m_Prefix + std::to_string(pPeter->GetCurrentHealth()));
}
