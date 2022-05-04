#pragma once
#include "BaseComponent.h"
#include "TileComponent.h"


class RenderComponent;
class TransformComponent;
class Texture2D;

class LevelComponent : public Component
{
public:
	LevelComponent(GameObject* go, int maxHeight, const std::string& tileSprite, const glm::ivec2& tileSize);
	~LevelComponent() override = default;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) noexcept = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void AddTile(const glm::ivec2& pos, TileType tile);

private:
	friend class TileComponent;
	bool GetPositionForTile(const glm::ivec2& location, glm::vec3& position);
	Texture2D* GetTexture() const { return m_pTexture; }
	glm::ivec2 GetTileSize() const { return m_TileSize; }



	static constexpr int m_Width = 9; // this is always 9 (at least in all the levels i played)
	const int m_Height = 6;
	const glm::ivec2 m_TileSize = {24, 16};


	const int m_HorizontalMargin = 20;
	// update these margin variables to be set by other components (e.g. UIElements)
	const int m_TopMargin = 60;
	const int m_BottomMargin = 120;

	Texture2D* m_pTexture = nullptr;
};

