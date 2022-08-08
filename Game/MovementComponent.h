#pragma once
#include <Component.h>


class RenderComponent;
class CollisionComponent;
class TransformComponent;
class LevelComponent;

class MovementComponent final : public Component
{
public:
	enum class Direction
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
	void SetMovementSpeed(float speed) { m_MoveSpeed = speed; }
	void SetDirection(Direction movement);
	void SetMoving(bool isMoving) { m_IsMoving = isMoving; }

private:
	LevelComponent* m_pLevel = nullptr;

	TransformComponent* m_pTransform = nullptr;
	CollisionComponent* m_pCollision = nullptr;

	Direction m_Movement = Direction::up;
	float m_MoveSpeed = 100.f;
	bool m_IsMoving = false;
};

