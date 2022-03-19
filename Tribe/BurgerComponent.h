#pragma once
#include "BaseComponent.h"


class BurgerComponent : public Component
{
public:
	BurgerComponent(GameObject* go);
	~BurgerComponent() override = default;
	BurgerComponent(const BurgerComponent&) = delete;
	BurgerComponent(BurgerComponent&&) noexcept = delete;
	BurgerComponent& operator=(const BurgerComponent&) = delete;
	BurgerComponent& operator=(BurgerComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void DropBurger() const;
};

