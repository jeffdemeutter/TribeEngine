#pragma once
#include <Component.h>

class TransformComponent;

class CollisionComponent : public Component
{
public:
	CollisionComponent(GameObject* pGo, TransformComponent* pTrans, float width, float height);
	~CollisionComponent() override = default;
	CollisionComponent(const CollisionComponent&) = delete;
	CollisionComponent(CollisionComponent&&) noexcept = delete;
	CollisionComponent& operator=(const CollisionComponent&) = delete;
	CollisionComponent& operator=(CollisionComponent&&) noexcept = delete;


	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	bool CheckCollision(const glm::vec2& position) const;
	bool CollisionDetection(CollisionComponent* const pCollision) const;

private:
	TransformComponent* m_pTransform = nullptr;

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
};

