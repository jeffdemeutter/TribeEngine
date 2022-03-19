#pragma once
#include "BaseComponent.h"

class PeterPepperComponent : public Component
{
public:
	PeterPepperComponent(GameObject* go);
	~PeterPepperComponent() override = default;
	PeterPepperComponent(const PeterPepperComponent&) = default;
	PeterPepperComponent(PeterPepperComponent&&) noexcept = default;
	PeterPepperComponent& operator=(const PeterPepperComponent&) = default;
	PeterPepperComponent& operator=(PeterPepperComponent&&) noexcept = default;

	virtual void Update() override;
	virtual void Render() const override{}

	void DoDamage();

	int GetCurrentHealth() const { return m_Health; }

	static int GetMaxHealth() { return m_MaxHealth; }

private:
	int m_Health = 3;

	static constexpr int m_MaxHealth = 3;
};
