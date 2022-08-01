#pragma once
#include "TankComponent.h"


enum class TankType
{
	blueTank,
	recognizer
};

class EnemyTankComponent : public TankComponent
{
public:
	EnemyTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement, TankType tankType);
	~EnemyTankComponent() override;
	EnemyTankComponent(const EnemyTankComponent&) = delete;
	EnemyTankComponent(EnemyTankComponent&&) noexcept = delete;
	EnemyTankComponent& operator=(const EnemyTankComponent&) = delete;
	EnemyTankComponent& operator=(EnemyTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext&) override {}

	void MovementAI();
	void SetTarget(GameObject* ptarget) { m_pTarget = ptarget; }
	void Kill();

private:
	GameObject* m_pTarget = nullptr;
};

