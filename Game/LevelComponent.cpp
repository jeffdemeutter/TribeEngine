#include "GamePCH.h"
#include "LevelComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TransformComponent.h"

#include "RenderManager.h"
#include <fstream>


std::string stringKey(int x, int y)
{
	return std::to_string(x) + " - " + std::to_string(y);
}

LevelComponent::LevelComponent(GameObject* pGo, TransformComponent* pTrans, const std::string& levelFile)
	: Component(pGo)
	, m_pTransform(pTrans)
{
	ParseLevelFile(levelFile);
}

LevelComponent::~LevelComponent()
{
	//SaveFile("../Data/Level3.bLevel");
}

#pragma region ColorStuff
bool CheckColor(float colOne, float colZero, float colChange)
{
	if (colOne < 1.f)
		return false;

	if (colZero > 0.f)
		return false;

	if (colChange <= 0.f && colChange >= 1.f)
		return false;

	return true;
}

void ColorChange(float colOne, float colZero, float& colChange, float delta, bool& rising)
{
	if (CheckColor(colOne, colZero, colChange))
	{
		if (rising)
		{
			colChange += delta;
			if (colChange > 1.f)
			{
				colChange = 1.f;
				rising = !rising;
			}
		}
		else
		{
			colChange -= delta;
			if (colChange < 0.f)
			{
				colChange = 0.f;
				rising = true;
			}
		}
	}
}

void RotateHueColor(glm::vec3& color, float delta)
{
	static bool rising = true;

	if (rising)
	{
		// rising 
		ColorChange(color.r, color.g, color.b, delta, rising);
		ColorChange(color.g, color.b, color.r, delta, rising);
		ColorChange(color.b, color.r, color.g, delta, rising);
	}
	else
	{
		// dropping
		ColorChange(color.b, color.g, color.r, delta, rising);
		ColorChange(color.r, color.b, color.g, delta, rising);
		ColorChange(color.g, color.r, color.b, delta, rising);
	}
}

#pragma endregion

void LevelComponent::Update(GameContext& gc)
{
	RotateHueColor(m_BackGroundColor, gc.pTime->GetDeltaTime() * m_ColorChangeSpeed);

	RenderManager::SetBackgroundColor(m_BackGroundColor);
}

void LevelComponent::AddObstacle(std::vector<glm::vec2> spline)
{
	if (spline.size() < 4)
		return;

	const auto& pos = m_pTransform->GetRelativePosition();

	for (glm::vec2& point : spline)
		point += pos;

	m_Obstacles.emplace_back(spline);
}

void LevelComponent::AddObstacles(const std::vector<std::vector<glm::vec2>>& obstacles)
{
	if (obstacles.empty())
		return;

	for (auto& spline : obstacles)
		AddObstacle(spline);
}

int GetRand(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

glm::vec2 LevelComponent::GetRandomPosition() const
{
	const auto& pos = m_pTransform->GetAbsolutePosition();

	return { float(GetRand(10, 590)) + pos.x, float(GetRand(10, 590)) + pos.y };
}

void LevelComponent::ParseLevelFile(const std::string& levelFile)
{
	std::ifstream in{ levelFile, std::ios::in | std::ios::binary };
	if (!in.is_open())
		return;

	// read obstacle count
	size_t obstacleCount{};
	in.read((char*)&obstacleCount, sizeof(int));
	m_Obstacles.reserve(obstacleCount);

	for (size_t i = 0; i < obstacleCount; ++i)
	{
		std::vector<glm::vec2>& Obstacle = m_Obstacles.emplace_back();

		// read size of obstacle
		size_t splineCount{};
		in.read((char*)&splineCount, sizeof(int));
		Obstacle.reserve(splineCount);

		for (size_t j = 0; j < splineCount; ++j)
		{
			// read vertex and store it
			glm::vec2& vertex = Obstacle.emplace_back();
			in.read((char*)&vertex, sizeof(glm::vec2));
		}
	}

	in.close();
}

void LevelComponent::SaveFile(const std::string& levelFile)
{
	std::ofstream of{ levelFile, std::ios::out | std::ios::binary};
	if (!of.is_open())
		return;
	

	// write obstacle count
	size_t obstacleCount = m_Obstacles.size();
	of.write((char*)&obstacleCount, sizeof(obstacleCount));

	for (auto& pObstacle : m_Obstacles)
	{
		// write size of obstacle
		size_t splineCount = pObstacle.size();
		of.write((char*)&splineCount, sizeof(int));

		for (glm::vec2& vertices : pObstacle)
		{
			// write all vertices
			of.write((char*)&vertices, sizeof(glm::vec2));
		}
	}

	of.close();
}

