#pragma once
#include <Component.h>


class RenderComponent;
class CollisionComponent;
class TransformComponent;
class LevelComponent;

class MovementComponent final : public Component
{
public:
	enum class Movement
	{
		right,
		down,
		left,
		up
	};

	MovementComponent(GameObject* pGo, TransformComponent* pTrans, CollisionComponent* pCollision);
	~MovementComponent() override;
	MovementComponent(const MovementComponent&) = delete;
	MovementComponent(MovementComponent&&) noexcept = delete;
	MovementComponent& operator=(const MovementComponent&) = delete;
	MovementComponent& operator=(MovementComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void SetLevelComponent(LevelComponent* pLevel) { m_pLevel = pLevel; }
	void SetMovement(Movement movement);

private:
	LevelComponent* m_pLevel = nullptr;

	TransformComponent* m_pTransform = nullptr;
	CollisionComponent* m_pCollision = nullptr;

	Movement m_Movement = Movement::up;
	float m_MoveSpeed = 100.f;
	bool m_IsMoving = false;
};

