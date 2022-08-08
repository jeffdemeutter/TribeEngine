#pragma once
#include "Component.h"

class TextComponent;

class LivesComponent : public Component
{
public:
	LivesComponent(GameObject* pGo, TextComponent* pText, int lives = 3);
	~LivesComponent() override = default;
	LivesComponent(const LivesComponent&) = delete;
	LivesComponent(LivesComponent&&) noexcept = delete;
	LivesComponent& operator=(const LivesComponent&) = delete;
	LivesComponent& operator=(LivesComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}

	void DecreaseLive();

private:
	int m_Lives;

	TextComponent* m_pTextComponent = nullptr;
};

