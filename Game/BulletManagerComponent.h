#pragma once
#include <Component.h>
#include <unordered_map>

class BulletConfigComponent;
class LevelComponent;
class BulletComponent;
class Command;
class TransformComponent;

class BulletManagerComponent final : public Component
{
public:
	BulletManagerComponent(GameObject* pGo, LevelComponent* pLevel);
	~BulletManagerComponent() override;
	BulletManagerComponent(const BulletManagerComponent&) = delete;
	BulletManagerComponent(BulletManagerComponent&&) noexcept = delete;
	BulletManagerComponent& operator=(const BulletManagerComponent&) = delete;
	BulletManagerComponent& operator=(BulletManagerComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void AddCollision(GameObject* pGo, Command* pCommand);
	void RemoveCollision(GameObject* pGo);
private:
	std::vector<GameObject*> m_pBullets;
	
	std::unordered_map<GameObject*, Command*> m_pGameObjects;

	LevelComponent* m_pLevelComponent = nullptr;

	void SpawnBullet(BulletConfigComponent* pBulletConfig);
};

