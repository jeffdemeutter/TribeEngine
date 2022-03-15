#include "TribePCH.h"
#include "RemainingLivesComponent.h"

#include "TextComponent.h"
#include "EventManager.h"
#include "PeterPepperComponent.h"

RemainingLivesComponent::RemainingLivesComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{


	EventManager::AddEventHandle(TookDamage, [this](GameObject* go) {this->UpdateLives(go); });
}

void RemainingLivesComponent::UpdateLives(GameObject* go)
{
	auto pPeter = go->GetComponent<PeterPepperComponent>();
	m_pTextComponent->SetText(m_Prefix + std::to_string(pPeter->GetCurrentHealth()));
}
