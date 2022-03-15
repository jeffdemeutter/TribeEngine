#pragma once
#include "BaseComponent.h"

class HealthComponent : public Component
{
public:
	HealthComponent(GameObject* go);
	~HealthComponent() override = default;
	HealthComponent(const HealthComponent&) = delete;
	HealthComponent(HealthComponent&&) noexcept = delete;
	HealthComponent& operator=(const HealthComponent&) = delete;
	HealthComponent& operator=(HealthComponent&&) noexcept = delete;

	bool IsDead() const { return m_Health <= 0; }
	void LoseHealth();
	void Kill();

	virtual void Update() override;
	virtual void Render() const override {};

private:
	int m_Health = 3;


};
