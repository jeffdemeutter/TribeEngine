#pragma once
#include <Component.h>

class TransformComponent;
class RenderComponent;

class TurretComponent final : public Component
{
public:
	TurretComponent(GameObject* pGo, int player, TransformComponent* pTrans, RenderComponent* pRender);
	~TurretComponent() override;
	TurretComponent(const TurretComponent&) = delete;
	TurretComponent(TurretComponent&&) noexcept = delete;
	TurretComponent& operator=(const TurretComponent&) = delete;
	TurretComponent& operator=(TurretComponent&&) noexcept = delete;


	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

private:
	TransformComponent* m_pTransform = nullptr;
	RenderComponent* m_pRender = nullptr;

	int m_Player = 0;

};

