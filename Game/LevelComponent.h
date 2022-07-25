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
	LevelComponent(GameObject* pGo);
	~LevelComponent() override = default;
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) noexcept = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override;
	virtual void Render() const override{}

	void AddObstacle(const std::vector<glm::vec2>& spline);
	void AddObstacles(const std::vector<std::vector<glm::vec2>>& obstacles);

	const std::vector<std::vector<glm::vec2>>& GetObstacles() const
	{
		return m_Obstacles;
	}

private:
	std::vector<std::vector<glm::vec2>> m_Obstacles;
	

	glm::vec3 m_BackGroundColor = { 1.f,0.f,0.f };
	float m_ColorChangeSpeed = 2.f;
};

