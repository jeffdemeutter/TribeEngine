#pragma once
#include "BaseComponent.h"

class LevelComponent;
class TransformComponent;

enum Direction
{
	left,
	top,
	right,
	bottom
};

class CrossComponent : public Component
{
public:
	CrossComponent(GameObject* go, LevelComponent* pLevel, TransformComponent* pTransform, const glm::ivec2& location);
	~CrossComponent() override = default;
	CrossComponent(const CrossComponent&) = delete;
	CrossComponent(CrossComponent&&) noexcept = delete;
	CrossComponent& operator=(const CrossComponent&) = delete;
	CrossComponent& operator=(CrossComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;


private:
	glm::ivec2 m_Location = { 0,0 };

	struct Connection
	{
		CrossComponent* pCrossComp = nullptr;
		Direction direction;
	};

	std::vector<Connection> m_pConnections;
};

