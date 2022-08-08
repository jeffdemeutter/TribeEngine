#include "GamePCH.h"
#include "ScoreComponent.h"

#include "ServiceLocator.h"
#include "EventEnum.h"
#include "EventManager.h"
#include "TextComponent.h"
#include <fstream>

ScoreComponent::ScoreComponent(GameObject* go, TextComponent* pText, const std::string& highScorePath)
	: Component(go)
	, m_pTextComponent(pText)
	, m_HighScorePath( "../Data/" + highScorePath)
{
	ServiceLocator::GetEventManager()->AddEventHandle(BlueTankDied, [this](GameObject* go, int type) { UpdateScore(go, type); });
	ServiceLocator::GetEventManager()->AddEventHandle(RedRecognizerDied, [this](GameObject* go, int type) { UpdateScore(go, type); });

	m_pTextComponent->SetBackgroundColor(SDL_Color{ 0,0,0,255 });
	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));

	HighScoreParser();
}
ScoreComponent::~ScoreComponent()
{
	SaveScore();

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

void ScoreComponent::SaveScore()
{
	m_HighScores.emplace_back(m_Score);
	std::ranges::sort(m_HighScores, [](const auto& a, const auto& b) { return a > b; });

	std::ofstream of{ m_HighScorePath, std::ios::out | std::ios::binary };
	if (!of.is_open())
		return;

	of.write((char*)m_HighScores.data(), sizeof(int) * 10);
	
	of.close();
}

void ScoreComponent::HighScoreParser()
{
	std::ifstream in{ m_HighScorePath, std::ios::in | std::ios::binary };
	if (!in.is_open())
		return;

	in.read((char*)m_HighScores.data(), sizeof(int) * 10);

	in.close();
}
