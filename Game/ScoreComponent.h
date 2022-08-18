#pragma once

#include "Component.h"

class TextComponent;
class ScoreComponent : public Component
{
public:
	ScoreComponent(GameObject* go, TextComponent* pText, const std::string& highScorePath);
	~ScoreComponent() override;
	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) noexcept = delete;

	virtual void Update(GameContext& ) override {}
	virtual void Render() const override {}

	void UpdateScore(GameObject* go, int type);
	void SaveScore();

	int GetScore(int i);

private:
	TextComponent* m_pTextComponent = nullptr;
	int m_Score = 0;
	std::string m_Prefix = "Score: ";

	std::vector<int> m_HighScores {0,0,0,0,0,0,0,0,0,0,0};
	std::string m_HighScorePath;
	void HighScoreParser();
};

