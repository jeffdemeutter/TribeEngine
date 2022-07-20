#pragma once
#include <Component.h>

enum class TileType;
class TileComponent;
class Texture2D;

class LevelComponent : public Component
{
public:
	LevelComponent(GameObject* pGo, const std::string& background , const std::string& spriteSheet, const glm::ivec2& tileSize);
	~LevelComponent() override = default;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) noexcept = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override {}

	TileComponent* AddTile(int x, int y, TileType tile, float rotation);

private:
	friend class TileComponent;
	bool GetPositionForTile(int x, int y, glm::vec3& position) const;
	Texture2D* GetTexture() const {	return m_pSpriteSheet; }
	glm::ivec2 GetTileSize() const { return m_TileSize; }

	static constexpr int m_Width = 17; 
	static constexpr int m_Height = 17;
	
	const glm::ivec2 m_TileSize = { 24, 24 };

	Texture2D* m_pSpriteSheet = nullptr;


	glm::vec3 m_BackGroundColor = { 1.f,0.f,0.f };
	float m_ColorChangeSpeed = 2.f;
};

