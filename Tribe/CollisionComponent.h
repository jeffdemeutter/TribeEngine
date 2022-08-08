#pragma once
#include "Component.h"

enum corners
{
	topLeft,
	topRight,
	bottomLeft,
	bottomRight
};

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
	bool CheckEdgeCollision(const glm::vec2& p1, const glm::vec2& p2) const;
	bool IsOverlapping(CollisionComponent* pCollision) const;

	glm::vec2 GetCornerPos(corners corner);

private:
	TransformComponent* m_pTransform = nullptr;

	std::vector<std::pair<CollisionComponent*, Command*>> m_pCollideChecks;

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
};

