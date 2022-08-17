#pragma once
#include "Component.h"

class BulletConfigComponent;
class LevelComponent;
class CollisionComponent;
class RenderComponent;
class MovementComponent;
class TransformComponent;

enum class TankType
{
	blueTank,
	recognizer
};

class EnemyTankComponent : public Component
{
public:
	EnemyTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, LevelComponent* pLevel, TankType tankType = TankType::recognizer, int lives = 3);
	~EnemyTankComponent() override;
	EnemyTankComponent(const EnemyTankComponent&) = delete;
	EnemyTankComponent(EnemyTankComponent&&) noexcept = delete;
	EnemyTankComponent& operator=(const EnemyTankComponent&) = delete;
	EnemyTankComponent& operator=(EnemyTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext&) override;

	void SetTarget(GameObject* ptarget);
	void Hit();

protected:
	TransformComponent* m_pTransform = nullptr;
	MovementComponent* m_pMovement = nullptr;

private:
	GameObject* m_pTarget = nullptr;

	RenderComponent* m_pRender = nullptr;
	CollisionComponent* m_pCollision = nullptr;
	LevelComponent* m_pLevel = nullptr;

	int m_Lives = 3;
	TankType m_Type;

	void MovementAI() const;
};

