#pragma once
#include "BaseComponent.h"

class TransformComponent;
class SpriteAnimationComponent;
class PeterPepperComponent : public Component
{
public:
	PeterPepperComponent(GameObject* go, TransformComponent* pTrans, SpriteAnimationComponent* pAnim);
	~PeterPepperComponent() override;
	PeterPepperComponent(const PeterPepperComponent&) = default;
	PeterPepperComponent(PeterPepperComponent&&) noexcept = default;
	PeterPepperComponent& operator=(const PeterPepperComponent&) = default;
	PeterPepperComponent& operator=(PeterPepperComponent&&) noexcept = default;

	enum SpriteMovements
	{
		idle,
		walkLeft,
		walkRight,
		climbUp,
		climbDown
	};

	virtual void Update() override;
	virtual void Render() const override{}

	void TakeDamage();
	void ChangeMovement(SpriteMovements movement) {
		m_ActiveMovement = movement;
	}

	int GetCurrentHealth() const { return m_Health; }
	static int GetMaxHealth() { return m_MaxHealth; }

private:
	int m_Health = 3;
	static constexpr int m_MaxHealth = 3;

	float m_MovementSpeed = 20.f;
	SpriteMovements m_ActiveMovement = idle;
	//SpriteMovements m_nextMovement = idle;

	SpriteAnimationComponent* m_pAnimComponent = nullptr;
	TransformComponent* m_pTransformComponent = nullptr;


	void DoMovement() const;
};
