#pragma once
#include "TankComponent.h"

class RenderComponent;
class MovementComponent;

class PlayerTankComponent final : public TankComponent
{
public:
	PlayerTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement);
	~PlayerTankComponent() override = default;
	PlayerTankComponent(const PlayerTankComponent&) = delete;
	PlayerTankComponent(PlayerTankComponent&&) noexcept = delete;
	PlayerTankComponent& operator=(const PlayerTankComponent&) = delete;
	PlayerTankComponent& operator=(PlayerTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext&) override {}

	void MoveUp() const;
	void MoveDown() const;
	void MoveLeft() const;
	void MoveRight() const;
};

