#pragma once
#include <Component.h>

class BulletConfigComponent;
class TransformComponent;
class RenderComponent;

class TurretComponent final : public Component
{
public:
	TurretComponent(GameObject* pGo, int player, TransformComponent* pTrans, RenderComponent* pRender, BulletConfigComponent* pBulletConfig);
	~TurretComponent() override;
	TurretComponent(const TurretComponent&) = delete;
	TurretComponent(TurretComponent&&) noexcept = delete;
	TurretComponent& operator=(const TurretComponent&) = delete;
	TurretComponent& operator=(TurretComponent&&) noexcept = delete;

	void SpawnBullet() const;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

private:
	TransformComponent* m_pTransform = nullptr;
	RenderComponent* m_pRender = nullptr;
	BulletConfigComponent* m_pBulletConfig = nullptr;

	glm::vec2 m_Direction = {1.f, 0.f};
	int m_Player = 0;

	
};

