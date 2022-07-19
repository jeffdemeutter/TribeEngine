#pragma once
#include "Component.h"
#include "glm/glm.hpp"

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

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void SetPosition(float x = 0, float y = 0) { m_RelativePosition = { x, y }; }
	void SetPosition(const glm::vec2& pos) { m_RelativePosition = pos; }
	void SetDepth(float depth) { m_Depth = depth; }

	glm::vec2 GetAbsolutePosition() const { return m_Position + m_RelativePosition; }
	glm::vec2& GetRelativePosition() { return m_RelativePosition; }
	float GetDepth() const { return m_Depth; }

protected:
	void UpdatePosition(const glm::vec2& pos) { m_Position = pos; }

private:
	// position should always be {0, 0} if object is on the root
	glm::vec2 m_Position = {0,0};
	glm::vec2 m_RelativePosition = { 0, 0 };
	float m_Depth;
};

