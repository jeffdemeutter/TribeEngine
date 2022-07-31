#pragma once
#include <Component.h>

class RenderComponent;
class MovementComponent;

class TankComponent : public Component
{
public:
	TankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement);
	~TankComponent() override;
	TankComponent(const TankComponent&) = delete;
	TankComponent(TankComponent&&) noexcept = delete;
	TankComponent& operator=(const TankComponent&) = delete;
	TankComponent& operator=(TankComponent&&) noexcept = delete;

	virtual void Render() const override = 0;
	virtual void Update(GameContext&) override = 0;

protected:
	RenderComponent* m_pRender = nullptr;
	MovementComponent* m_pMovement = nullptr;
};

