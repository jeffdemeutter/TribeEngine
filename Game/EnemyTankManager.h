#pragma once
#include <Component.h>

#include "EnemyTankComponent.h"

class BulletManagerComponent;
class LevelComponent;

class EnemyTankManager : public Component
{
public:
	EnemyTankManager(GameObject* pGo, LevelComponent* pLevel, BulletManagerComponent* pBulletManager);
	~EnemyTankManager() override = default;
	EnemyTankManager(const EnemyTankManager&) = delete;
	EnemyTankManager(EnemyTankManager&&) noexcept = delete;
	EnemyTankManager& operator=(const EnemyTankManager&) = delete;
	EnemyTankManager& operator=(EnemyTankManager&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}

	EnemyTankComponent* AddEnemy(TankType type, bool initialSpawn = true);

private:
	int m_EnemyCountType1 = 0;
	int m_EnemyCountType2 = 0;

	LevelComponent* m_pLevel = nullptr;
	BulletManagerComponent* m_pBulletManager = nullptr;

	void RespawnEnemies(GameObject* pPlayerTarget);
};

