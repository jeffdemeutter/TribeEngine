#pragma once
#include "Component.h"

class TextComponent;
class ScoreComponent : public Component
{
public:
	ScoreComponent(GameObject* go, TextComponent* pText);
	~ScoreComponent() override;
	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) noexcept = delete;

	void UpdateScore(GameObject* go, int type);

	virtual void Update(GameContext& ) override {}
	virtual void Render() const override {}

private:
	TextComponent* m_pTextComponent = nullptr;
	int m_Score = 0;
	std::string m_Prefix = "Score: ";
};

