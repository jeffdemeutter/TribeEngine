#pragma once
#include <Component.h>

class CollisionComponent;
class TransformComponent;

class BulletComponent final : public Component
{
public:
	BulletComponent(GameObject* pGo, TransformComponent* pTrans, const glm::vec2& direction, float speed);
	~BulletComponent() override;
	BulletComponent(const BulletComponent&) = delete;
	BulletComponent(BulletComponent&&) noexcept = delete;
	BulletComponent& operator=(const BulletComponent&) = delete;
	BulletComponent& operator=(BulletComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}


private:
	TransformComponent* m_pTransform = nullptr;

	float m_Speed = 300.f;
	glm::vec2 m_Direction = {0.f, 1.f};

	int m_Bounces = 0;
	static constexpr int m_BouncesMax = 5;

	// makes sure bullets dissapear after some time
	float m_Duration = 0.f;
	static constexpr float m_MaxDuration = 25.f;

	void Destroy() const;
};

