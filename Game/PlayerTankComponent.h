#pragma once
#include <Component.h>

class RenderComponent;
class MovementComponent;

class PlayerTankComponent final : public Component
{
public:
	PlayerTankComponent(GameObject* pGo, RenderComponent* pRender, MovementComponent* pMovement);
	~PlayerTankComponent() override;
	PlayerTankComponent(const PlayerTankComponent&) = delete;
	PlayerTankComponent(PlayerTankComponent&&) noexcept = delete;
	PlayerTankComponent& operator=(const PlayerTankComponent&) = delete;
	PlayerTankComponent& operator=(PlayerTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext& gc) override;

	void MoveUp() const;
	void MoveDown() const;
	void MoveLeft() const;
	void MoveRight() const;

private:
	RenderComponent* m_pRender = nullptr;
	MovementComponent* m_pMovement = nullptr;
};

