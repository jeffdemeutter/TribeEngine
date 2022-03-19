#include "TribePCH.h"
#include "PointsDisplayComponent.h"

#include "TextComponent.h"

PointsDisplayComponent::PointsDisplayComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{

	EventManager::AddEventHandle(EnemyDied, [this](GameObject* go, EventType type) { UpdateScore(go, type); });
	EventManager::AddEventHandle(BurgerDrop, [this](GameObject* go, EventType type) { UpdateScore(go, type); });


	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));
}
PointsDisplayComponent::~PointsDisplayComponent()
{
	m_pTextComponent = nullptr;
}

void PointsDisplayComponent::UpdateScore(GameObject*, EventType type)
{
	switch (type)
	{
	case EnemyDied:
		m_Score += 10;
		break;
	case BurgerDrop:
		m_Score += 20;
		break;
	}

	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));
}

void PointsDisplayComponent::Update()
{
	
}

void PointsDisplayComponent::Render() const
{
	
}

