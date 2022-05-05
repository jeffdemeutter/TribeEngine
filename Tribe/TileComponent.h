#pragma once
#include "BaseComponent.h"
#include "BurgerComponent.h"

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

// overwritten thse operators so the enumerator behaves like flags
constexpr TileType operator|(TileType a, TileType b)
{
	return static_cast<TileType>(static_cast<int>(a) | static_cast<int>(b));
}
constexpr bool operator==(TileType a, TileType b)
{
	return static_cast<bool>(static_cast<int>(a) & static_cast<int>(b));
}

class TileComponent : public Component
{
public:
	TileComponent(GameObject* go, int x, int y, LevelComponent* pLevel, TransformComponent* pTransform, RenderComponent* pRender, TileType tile);
	~TileComponent() override = default;
	TileComponent(const TileComponent&) = delete;
	TileComponent(TileComponent&&) noexcept = delete;
	TileComponent& operator=(const TileComponent&) = delete;
	TileComponent& operator=(TileComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void AddBurgerObject(BurgerComponent::BurgerType type) const;
	void SetStartPosition(GameObject* go);

private:
	glm::ivec2 m_Location = { 0,0 };
	TransformComponent* m_pTransform = nullptr;
	LevelComponent* m_pLevel = nullptr;

	static SDL_Rect GetCorrespondingSrcRect(TileType tile, LevelComponent* pLevel);
	glm::vec3 GetBurgerPosition() const;
};

