#pragma once
#include <Component.h>

#include "EnemyTankComponent.h"

class BulletManagerComponent;
class LevelComponent;

class EnemyTankManager : public Component
{
public:
	EnemyTankManager(GameObject* pGo, GameObject* pTarget, LevelComponent* pLevel, BulletManagerComponent* pBulletManager);
	~EnemyTankManager() override = default;
	EnemyTankManager(const EnemyTankManager&) = delete;
	EnemyTankManager(EnemyTankManager&&) noexcept = delete;
	EnemyTankManager& operator=(const EnemyTankManager&) = delete;
	EnemyTankManager& operator=(EnemyTankManager&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	EnemyTankComponent* AddEnemy(TankType type, bool initial = true);

private:
	int m_RecognizerCount{};
	int m_BlueTankCount{};

	GameObject* m_pTarget = nullptr;
	LevelComponent* m_pLevel = nullptr;
	BulletManagerComponent* m_pBulletManager = nullptr;

	void DeleteEnemies();
	void RespawnEnemies();
};

