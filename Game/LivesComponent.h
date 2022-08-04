#pragma once
#include "Component.h"

class LivesComponent : public Component
{
public:
	LivesComponent(GameObject* pGo, int lives = 3);
	~LivesComponent() override = default;
	LivesComponent(const LivesComponent&) = delete;
	LivesComponent(LivesComponent&&) noexcept = delete;
	LivesComponent& operator=(const LivesComponent&) = delete;
	LivesComponent& operator=(LivesComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}


private:
	int m_Lives;

};

