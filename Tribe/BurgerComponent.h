#pragma once
#include "BaseComponent.h"


class RenderComponent;
class BurgerComponent : public Component
{
public:
	enum BurgerType
	{
		bunTop,
		bunBottom,
		burger,
		salad,
		tomato,
		cheese
	};

	BurgerComponent(GameObject* go, RenderComponent* pRender, BurgerType type, const glm::vec3& position);
	~BurgerComponent() override = default;
	BurgerComponent(const BurgerComponent&) = delete;
	BurgerComponent(BurgerComponent&&) noexcept = delete;
	BurgerComponent& operator=(const BurgerComponent&) = delete;
	BurgerComponent& operator=(BurgerComponent&&) noexcept = delete;


	virtual void Update() override;
	virtual void Render() const override;

	void DropBurger() const;

private:
	void InitBurgerType(RenderComponent* pRender, BurgerType type);
};

