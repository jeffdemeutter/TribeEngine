#pragma once
#include "Component.h"


class Command;
class TransformComponent;

class CollisionComponent : public Component
{
public:
	CollisionComponent(GameObject* pGo, TransformComponent* pTrans, float width, float height);
	~CollisionComponent() override;
	CollisionComponent(const CollisionComponent&) = delete;
	CollisionComponent(CollisionComponent&&) noexcept = delete;
	CollisionComponent& operator=(const CollisionComponent&) = delete;
	CollisionComponent& operator=(CollisionComponent&&) noexcept = delete;


	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void AddColliderCheck(CollisionComponent* pCollision, Command* pCommand);

	bool CheckCollision(const glm::vec2& position) const;
	bool CollisionDetection(CollisionComponent* pCollision) const;


private:
	TransformComponent* m_pTransform = nullptr;

	std::vector<std::pair<CollisionComponent*, Command*>> m_pCollideChecks;

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
};

