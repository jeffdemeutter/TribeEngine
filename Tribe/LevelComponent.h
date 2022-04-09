#pragma once
#include "BaseComponent.h"


class LevelComponent : public Component
{
public:
	LevelComponent(GameObject* go, int maxHeight);
	~LevelComponent() override = default;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) noexcept = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	bool GetPositionForCrossSection(const glm::ivec2& location, glm::vec3& position);

private:
	static constexpr int m_Width = 5;
	const int m_Height = 6;

	const int m_HorizontalMargin = 20;
	// update these margin variables to be set by other components (e.g. UIElements)
	const int m_TopMargin = 60;
	const int m_BottomMargin = 120;
};

