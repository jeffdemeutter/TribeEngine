#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

class TransformComponent final : public Component
{
public:
	TransformComponent(GameObject* go) : Component(go) {}
	TransformComponent(GameObject* go, int x, int y, int z = 0);
	TransformComponent(GameObject* go, const glm::vec3& pos);
	~TransformComponent() override = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(TransformComponent&&) noexcept = default;
	TransformComponent& operator=(const TransformComponent&) = default;
	TransformComponent& operator=(TransformComponent&&) noexcept = default;


	virtual void Update() override {}
	virtual void Render() const override {}

	[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }

	void SetPosition(float x, float y);
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& pos);
private:
	glm::vec3 m_Position = {0,0,0};
};

