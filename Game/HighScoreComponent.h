#pragma once
#include <Component.h>

class TextComponent;
class Font;
class ScoreComponent;

class HighScoreComponent : public Component
{
public:
	HighScoreComponent(GameObject* pGo, ScoreComponent* pScore, Font* pFont);
	~HighScoreComponent() override = default;
	HighScoreComponent(const HighScoreComponent&) = delete;
	HighScoreComponent(HighScoreComponent&&) noexcept = delete;
	HighScoreComponent& operator=(const HighScoreComponent&) = delete;
	HighScoreComponent& operator=(HighScoreComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override{}

private:
	std::vector<TextComponent*> m_pTexts;
	ScoreComponent* m_pScore = nullptr;
	Font* m_pFont = nullptr;

	static constexpr int m_Height = 40;
};

