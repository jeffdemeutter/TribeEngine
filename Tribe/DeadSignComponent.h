#pragma once
#include "BaseComponent.h"
#include "EventManager.h"

class TextComponent;
class DeadSignComponent : public Component
{
public:
	DeadSignComponent(GameObject* go, TextComponent* pText);
	~DeadSignComponent() override = default;
	DeadSignComponent(const DeadSignComponent&) = delete;
	DeadSignComponent(DeadSignComponent&&) noexcept = delete;
	DeadSignComponent& operator=(const DeadSignComponent&) = delete;
	DeadSignComponent& operator=(DeadSignComponent&&) noexcept = delete;

	virtual void Update() override {};
	virtual void Render() const override {};

	void NotifyDead(GameObject* go, EventType type);

private:
	TextComponent* m_pTextComponent = nullptr;
};

