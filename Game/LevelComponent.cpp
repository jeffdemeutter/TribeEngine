#include "GamePCH.h"
#include "LevelComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "TileComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"


LevelComponent::LevelComponent(GameObject* pGo, const std::string& background, const std::string& spriteSheet, const glm::ivec2& tileSize)
	: Component(pGo)
	, m_TileSize(tileSize)
	, m_pSpriteSheet(ResourceManager::LoadTexture(spriteSheet))
{
	const auto pLevel = GetParent();

	const auto pTrans = pLevel->AddComponent(new TransformComponent(pLevel));
	const auto pRender = pLevel->AddComponent(new RenderComponent(pLevel, pTrans, background));
	pRender->SetFullScreen(true);
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

TileComponent* LevelComponent::AddTile(int x, int y, TileType tile, float rotation)
{
	const auto pGo = GetParent()->AddGameObject(std::to_string(x) + " - " + std::to_string(y));
	
	const auto pTrans = pGo->AddComponent(new TransformComponent(pGo));
	const auto pRender = pGo->AddComponent(new RenderComponent(pGo, pTrans));
	const auto pTile = pGo->AddComponent(new TileComponent(pGo, x, y, this, pTrans, pRender, tile, rotation));

	return pTile;
}

bool LevelComponent::GetPositionForTile(int x, int y, glm::vec3& position) const
{
	if (x < 0 || x >= m_Width)
		std::cout << "Tile location X " << x << " is out of bounds \n";

	if (y < 0 || y >= m_Height)
		std::cout << "Tile location Y " << y << " is out of bounds \n";


	// formula to calculate where the crossection should be rendered

	// remove the margin from both sides from window
	position.x = float(RenderManager::GetWindowSize().x);
	position.y = float(RenderManager::GetWindowSize().y);
	// divide by levelWidth/Height and multiply with the location.x/y to find the position
	position.x /= float(m_Width);
	position.x += float(m_TileSize.x * x);

	position.y /= float(m_Height);
	position.y += float(m_TileSize.y * y);

	return true;
}
