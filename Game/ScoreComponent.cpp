#include "GamePCH.h"
#include "ScoreComponent.h"

#include "ServiceLocator.h"
#include "EventEnum.h"
#include "EventManager.h"
#include "TextComponent.h"

ScoreComponent::ScoreComponent(GameObject* go, TextComponent* pText)
	: Component(go)
	, m_pTextComponent(pText)
{
	ServiceLocator::GetEventManager()->AddEventHandle(BlueTankDied, [this](GameObject* go, int type) { UpdateScore(go, type); });
	ServiceLocator::GetEventManager()->AddEventHandle(RedRecognizerDied, [this](GameObject* go, int type) { UpdateScore(go, type); });


	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));
}
ScoreComponent::~ScoreComponent()
{
	m_pTextComponent = nullptr;
}

void ScoreComponent::UpdateScore(GameObject*, int type)
{
	switch (type)
	{
	case BlueTankDied:
		m_Score += 100;
		break;
	case RedRecognizerDied:
		m_Score += 250;
		break;
	}

	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));
}
