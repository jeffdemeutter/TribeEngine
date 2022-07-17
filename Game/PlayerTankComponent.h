#pragma once
#include <Component.h>

class RenderComponent;
class SpriteAnimationComponent;
class TransformComponent;

class PlayerTankComponent final : public Component
{
public:
	enum class Movement
	{
		right	= 0,
		down	= 90,
		left	= 180,
		up		= 270
	};

	PlayerTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender);
	~PlayerTankComponent() override;
	PlayerTankComponent(const PlayerTankComponent&) = delete;
	PlayerTankComponent(PlayerTankComponent&&) noexcept = delete;
	PlayerTankComponent& operator=(const PlayerTankComponent&) = delete;
	PlayerTankComponent& operator=(PlayerTankComponent&&) noexcept = delete;

	virtual void Render() const override {}
	virtual void Update(GameContext& gc) override;

	void DoMovement(Movement movement);

private:
	enum Sprite
	{
		vertical,
		horizontal
	};

	TransformComponent* m_pTransform = nullptr;
	RenderComponent* m_pRender = nullptr;
	Movement m_Movement = Movement::up;
	float m_MoveSpeed = 100.f;
	bool m_IsMoving = false;
};

