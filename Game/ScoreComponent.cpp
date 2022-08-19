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
	const auto& updateScoreLambda = [this](GameObject* go, int type)
	{
		UpdateScore(go, type);
	};
	ServiceLocator::GetEventManager()->AddEventHandle(BlueTankDied, updateScoreLambda );
	ServiceLocator::GetEventManager()->AddEventHandle(RecognizerDied, updateScoreLambda);

	ServiceLocator::GetEventManager()->AddEventHandle(GameOver, [this](GameObject*, int)
	{
		SaveScore();
	});

	m_pTextComponent->SetBackgroundColor(SDL_Color{ 0,0,0,255 });
	m_pTextComponent->SetText(m_Prefix + std::to_string(m_Score));

	HighScoreParser();
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
	case RecognizerDied:
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

int ScoreComponent::GetScore(int i)
{
	if (i > 10)
		return 0;

	if (i < 0)
		return 0;

	return m_HighScores[i];
}

void ScoreComponent::HighScoreParser()
{
	std::ifstream in{ m_HighScorePath, std::ios::in | std::ios::binary };
	if (!in.is_open())
		return;

	in.read((char*)m_HighScores.data(), sizeof(int) * 10);

	in.close();
}
