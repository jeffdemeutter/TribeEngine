#pragma once
#include <Component.h>

class Command;
class CollisionComponent;

class ButtonComponent : public Component
{
public:
	ButtonComponent(GameObject* pGo, CollisionComponent* pCollision, Command* pCommand);
	~ButtonComponent() override;
	ButtonComponent(const ButtonComponent&) = delete;
	ButtonComponent(ButtonComponent&&) noexcept = delete;
	ButtonComponent& operator=(const ButtonComponent&) = delete;
	ButtonComponent& operator=(ButtonComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}

	void CheckIfClicked() const;

private:
	CollisionComponent* m_pCollision = nullptr;
	Command* m_pCommand = nullptr;
};

