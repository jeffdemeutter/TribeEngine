#pragma once
#include "Component.h"

class GameObject;

class TransformComponent : public Component
{
public:
	~TransformComponent() override = default;
	TransformComponent(const TransformComponent&) = delete;
	TransformComponent(TransformComponent&&) noexcept = delete;
	TransformComponent& operator=(const TransformComponent&) = delete;
	TransformComponent& operator=(TransformComponent&&) noexcept = delete;

	TransformComponent(GameObject* pGo, float x = 0.f, float y = 0.f, float depth = 0.5f);
	TransformComponent(GameObject* pGo, const glm::vec2& pos, float depth = 0.5f);
		

	virtual void Update() override {}
	virtual void Render() const override {}

	void SetPosition(float x = 0, float y = 0) { m_Position = { x, y }; }
	void SetPosition(const glm::vec2& pos) { m_Position = pos; }
	void SetDepth(float depth) { m_Depth = depth; }

private:
	glm::vec2 m_Position;
	float m_Depth;
};

