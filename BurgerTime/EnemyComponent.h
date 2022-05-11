#pragma once
#include "BaseComponent.h"


class EnemyComponent : public Component
{
public:
	EnemyComponent(GameObject* go);
	~EnemyComponent() override = default;
	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) noexcept = delete;
	EnemyComponent& operator=(const EnemyComponent&) = delete;
	EnemyComponent& operator=(EnemyComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void KillEnemy() const;

};

