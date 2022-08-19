#include "GamePCH.h"
#include "HighScoreComponent.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"

HighScoreComponent::HighScoreComponent(GameObject* pGo, ScoreComponent* pScore, Font* pFont)
	: Component(pGo)
	, m_pScore(pScore)
	, m_pFont(pFont)
{
	const auto pGameOverScreen = GetParent();

	for (int i = 0; i < 10; ++i)
	{
		const auto pHighScoreList = pGameOverScreen->AddGameObject("Highscore" + std::to_string(i));

		const auto pTrans = pHighScoreList->AddComponent(new TransformComponent(pHighScoreList, 350, float(200 + i * m_Height)));
		const auto pRender = pHighScoreList->AddComponent(new RenderComponent(pHighScoreList, pTrans));
		m_pTexts.emplace_back(pHighScoreList->AddComponent(new TextComponent(pHighScoreList, pRender, " ", m_pFont)));
	}
}

void HighScoreComponent::Update(GameContext&)
{
	for (size_t i = 0; i < m_pTexts.size(); ++i)
	{
		const int score = m_pScore->GetScore(int(i));

		m_pTexts[i]->SetText(std::to_string(i + 1) + ": " + std::to_string(score));
	}
}
