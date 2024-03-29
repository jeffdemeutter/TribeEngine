﻿#include "TribePCH.h"
#include "RemainingLivesComponent.h"

#include "TextComponent.h"
#include "PeterPepperComponent.h"

RemainingLivesComponent::RemainingLivesComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{


	ServiceLocator::GetEventManager()->AddEventHandle(TookDamage, [this](GameObject* go, EventType type) { UpdateLives(go, type); });

	m_pTextComponent->SetText(m_Prefix + std::to_string(PeterPepperComponent::GetMaxHealth()));
}

RemainingLivesComponent::~RemainingLivesComponent()
{
	m_pTextComponent = nullptr;	
}

void RemainingLivesComponent::UpdateLives(GameObject* go, EventType) const
{
	const auto pPeter = go->GetComponent<PeterPepperComponent>();
	m_pTextComponent->SetText(m_Prefix + std::to_string(pPeter->GetCurrentHealth()));
}
