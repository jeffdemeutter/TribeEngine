#include "GamePCH.h"
#include "LevelComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TransformComponent.h"

#include "RenderManager.h"


std::string stringKey(int x, int y)
{
	return std::to_string(x) + " - " + std::to_string(y);
}

LevelComponent::LevelComponent(GameObject* pGo, TransformComponent* pTrans)
	: Component(pGo)
	, m_pTransform(pTrans)
{	
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
