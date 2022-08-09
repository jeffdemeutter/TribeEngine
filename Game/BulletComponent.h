#pragma once
#include <Component.h>

class LevelComponent;
class CollisionComponent;
class TransformComponent;

class BulletComponent final : public Component
{
public:
	BulletComponent(GameObject* pGo, TransformComponent* pTrans, LevelComponent* pLevel, const glm::vec2& direction, float speed, GameObject* pParent);
	~BulletComponent() override;
	BulletComponent(const BulletComponent&) = delete;
	BulletComponent(BulletComponent&&) noexcept = delete;
	BulletComponent& operator=(const BulletComponent&) = delete;
	BulletComponent& operator=(BulletComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	GameObject* GetOriginFired() const { return m_pOriginObject; }
	void SetCanBeDestroyed() { m_CanBeDestroyed = true; }
	bool CanBeDestroyed() const { return m_CanBeDestroyed; }
private:
	TransformComponent* m_pTransform = nullptr;
	LevelComponent* m_pLevel = nullptr;
	GameObject* m_pOriginObject = nullptr;

	float m_Speed = 300.f;
	glm::vec2 m_Direction = {0.f, 1.f};

	bool m_CanBeDestroyed = false;

	int m_Bounces = 0;
	static constexpr int m_BouncesMax = 5;

	// makes sure bullets dissapear after some time
	float m_Duration = 0.f;
	static constexpr float m_MaxDuration = 25.f;
};

