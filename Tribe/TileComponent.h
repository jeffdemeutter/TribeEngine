#pragma once
#include "BaseComponent.h"

class RenderComponent;
class LevelComponent;
class TransformComponent;

// bitset to set where the tiles go towards
enum class TileType
{
	left	= 0b000001,
	top		= 0b000010,
	right	= 0b000100,
	bottom	= 0b001000,
	platform= 0b010000,
	ladder	= 0b100000
};

constexpr  TileType operator|(TileType a, TileType b)
{
	return static_cast<TileType>(static_cast<int>(a) | static_cast<int>(b));
}
constexpr  bool operator==(TileType a, TileType b)
{
	return static_cast<bool>(static_cast<int>(a) & static_cast<int>(b));
}

class TileComponent : public Component
{
public:
	TileComponent(GameObject* go, LevelComponent* pLevel, TransformComponent* pTransform, const glm::ivec2& location, RenderComponent* pRender, TileType tile);
	~TileComponent() override = default;
	TileComponent(const TileComponent&) = delete;
	TileComponent(TileComponent&&) noexcept = delete;
	TileComponent& operator=(const TileComponent&) = delete;
	TileComponent& operator=(TileComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;


private:
	glm::ivec2 m_Location = { 0,0 };


	static SDL_Rect GetCorrespondingSrcRect(TileType tile, LevelComponent* pLevel);
};

