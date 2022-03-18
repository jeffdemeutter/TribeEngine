#pragma once
#include "BaseComponent.h"
#include "EventManager.h"

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

	void UpdateScore(GameObject* go, EventType type);

	virtual void Update() override;
	virtual void Render() const override;

private:
	TextComponent* m_pTextComponent = nullptr;
	int m_Score = 0;
};

