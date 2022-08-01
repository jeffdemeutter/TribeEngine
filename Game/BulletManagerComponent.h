#pragma once
#include <Component.h>

class Command;
class TransformComponent;
class CollisionComponent;

class BulletManagerComponent final : public Component
{
public:
	BulletManagerComponent(GameObject* pGo);
	~BulletManagerComponent() override;
	BulletManagerComponent(const BulletManagerComponent&) = delete;
	BulletManagerComponent(BulletManagerComponent&&) noexcept = delete;
	BulletManagerComponent& operator=(const BulletManagerComponent&) = delete;
	BulletManagerComponent& operator=(BulletManagerComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void AddCollision(CollisionComponent* pCollision, Command* pCommand);

	void SpawnBullet(const glm::vec2& pos, const glm::vec2& dir);

private:
	std::vector<TransformComponent*> m_pBullets;

	std::vector<std::pair<CollisionComponent*, Command*>> m_pCollisions;
};

