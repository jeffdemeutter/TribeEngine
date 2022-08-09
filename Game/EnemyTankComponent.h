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
	EnemyTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, BulletConfigComponent* pBulletConfig, LevelComponent* pLevel, TankType tankType, int lives = 3);
	~EnemyTankComponent() override;
	EnemyTankComponent(const EnemyTankComponent&) = delete;
	EnemyTankComponent(EnemyTankComponent&&) noexcept = delete;
	EnemyTankComponent& operator=(const EnemyTankComponent&) = delete;
	EnemyTankComponent& operator=(EnemyTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext&) override;

	void SetTarget(GameObject* ptarget) { m_pTarget = ptarget; }
	void Hit();
private:
	GameObject* m_pTarget = nullptr;

	TransformComponent* m_pTransform = nullptr;
	RenderComponent* m_pRender = nullptr;
	CollisionComponent* m_pCollision = nullptr;
	MovementComponent* m_pMovement = nullptr;
	BulletConfigComponent* m_pBulletConfig = nullptr;
	LevelComponent* m_pLevel = nullptr;

	int m_Lives = 3;
	TankType m_Type;

	bool m_CanShoot = false;
	float m_Timer = 0.f;
	float m_TimerMax = 2.f;

	void MovementAI();
};

