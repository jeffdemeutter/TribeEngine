#include "TribePCH.h"
#include "PointsDisplayComponent.h"

PointsDisplayComponent::PointsDisplayComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{

	EventManager::AddEventHandle(EnemyDied, [this](GameObject* go, EventType type) { UpdateScore(go, type); });
	EventManager::AddEventHandle(BurgerDrop, [this](GameObject* go, EventType type) { UpdateScore(go, type); });
}
PointsDisplayComponent::~PointsDisplayComponent()
{
	m_pTextComponent = nullptr;
}

void PointsDisplayComponent::UpdateScore(GameObject*, EventType type)
{
	switch (type)
	{
		
	}
}

void PointsDisplayComponent::Update()
{
	
}

void PointsDisplayComponent::Render() const
{
	
}

