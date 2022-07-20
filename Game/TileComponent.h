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
	cross
};


class TileComponent : public Component
{
public:
	TileComponent(GameObject* go, int x, int y, LevelComponent* pLevel, TransformComponent* pTransform, RenderComponent* pRender, TileType tile, float rotation);
	~TileComponent() override = default;
	TileComponent(const TileComponent&) = delete;
	TileComponent(TileComponent&&) noexcept = delete;
	TileComponent& operator=(const TileComponent&) = delete;
	TileComponent& operator=(TileComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}
	

private:
	glm::ivec2 m_Location = { 0,0 };
	TransformComponent* m_pTransform = nullptr;
	LevelComponent* m_pLevel = nullptr;

	const glm::vec3 m_pPawnOffsets = { 4, -10, 0 };
};
