#pragma once
#include "EnemyTankComponent.h"

class BulletConfigComponent;
class LevelComponent;
class CollisionComponent;
class RenderComponent;
class MovementComponent;
class TransformComponent;

class EnemyTank2Component : public EnemyTankComponent
{
public:
	EnemyTank2Component(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, BulletConfigComponent* pBulletConfig, LevelComponent* pLevel);
	~EnemyTank2Component() override = default;
	EnemyTank2Component(const EnemyTank2Component&) = delete;
	EnemyTank2Component(EnemyTank2Component&&) noexcept = delete;
	EnemyTank2Component& operator=(const EnemyTank2Component&) = delete;
	EnemyTank2Component& operator=(EnemyTank2Component&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext&) override;


private:
	BulletConfigComponent* m_pBulletConfig = nullptr;

	bool m_CanShoot = false;
	float m_Timer = 0.f;
	float m_TimerMax = 2.f;
};

