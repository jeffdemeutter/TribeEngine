#pragma once
#include <Component.h>

class TransformComponent;

class BulletComponent final : public Component
{
public:
	BulletComponent(GameObject* pGo, TransformComponent* pTrans);
	~BulletComponent() override;
	BulletComponent(const BulletComponent&) = delete;
	BulletComponent(BulletComponent&&) noexcept = delete;
	BulletComponent& operator=(const BulletComponent&) = delete;
	BulletComponent& operator=(BulletComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override;


private:
	TransformComponent* m_pTransform = nullptr;

};

