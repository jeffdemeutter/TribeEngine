#pragma once
#include "Component.h"

class TextComponent;
class PointsDisplayComponent : public Component
{
public:
	PointsDisplayComponent(GameObject* go, TextComponent* pText);
	~PointsDisplayComponent() override;
	PointsDisplayComponent(const PointsDisplayComponent&) = delete;
	PointsDisplayComponent(PointsDisplayComponent&&) noexcept = delete;
	PointsDisplayComponent& operator=(const PointsDisplayComponent&) = delete;
	PointsDisplayComponent& operator=(PointsDisplayComponent&&) noexcept = delete;

	void UpdateScore(GameObject* go, int type);

	virtual void Update(GameContext& ) override {}
	virtual void Render() const override {}

private:
	TextComponent* m_pTextComponent = nullptr;
	int m_Score = 0;
	std::string m_Prefix = "Score: ";
};

