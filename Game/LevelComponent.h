#pragma once
#include <Component.h>
#include <unordered_map>

class TransformComponent;
class RenderComponent;
enum class TileType;
class TileComponent;
class Texture2D;

class LevelComponent : public Component
{
public:
	LevelComponent(GameObject* pGo, RenderComponent* pRender, const std::string& spriteSheet, const glm::ivec2& tileSize, const glm::ivec2& gridSize);
	~LevelComponent() override = default;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) noexcept = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	void AddTile(int x, int y, TileType tile, float rotation = 0);
	void GenerateWalls();

	[[nodiscard]] std::vector<GameObject*> GetNearbyTiles(glm::vec2 pos, float radius) const;

private:
	std::unordered_map <std::string, GameObject*> m_Tiles;
	glm::vec2 GetPositionForTile(int x, int y) const;

	static constexpr int m_Width = 18; 
	static constexpr int m_Height = 18;
	
	const glm::ivec2 m_TileSize = { 24, 24 };
	const glm::ivec2 m_GridSize = { 24,24 };
	
	Texture2D* m_pSpriteSheet = nullptr;

	glm::vec3 m_BackGroundColor = { 1.f,0.f,0.f };
	float m_ColorChangeSpeed = 2.f;
	SDL_Rect GetSrcRect(TileType tile) const;
};

