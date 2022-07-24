#pragma once
#include <Component.h>

class RenderComponent;
class TransformComponent;
class LevelComponent;

// bitset to set where the tiles go towards
enum class TileType
{
	end,
	corner,
	straight,
	tPoint,
	cross,
	wall
};


class TileComponent : public Component
{
public:
	TileComponent(GameObject* go, int x, int y, TileType tile, float rotation);
	~TileComponent() override = default;
	TileComponent(const TileComponent&) = delete;
	TileComponent(TileComponent&&) noexcept = delete;
	TileComponent& operator=(const TileComponent&) = delete;
	TileComponent& operator=(TileComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}

	TileType GetType() const { return m_Type; }

private:
	glm::ivec2 m_Location = { 0,0 };
	TileType m_Type;
	float m_Rotation = 0;
};
