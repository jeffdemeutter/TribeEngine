#include "GamePCH.h"
#include "LevelComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TileComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include "RenderManager.h"
#include "ResourceManager.h"


std::string stringKey(int x, int y)
{
	return std::to_string(x) + " - " + std::to_string(y);
}

LevelComponent::LevelComponent(GameObject* pGo, RenderComponent* pRender, const std::string& spriteSheet, const glm::ivec2& tileSize, const glm::ivec2& gridSize)
	: Component(pGo)
	, m_TileSize(tileSize)
	, m_GridSize(gridSize)
	, m_pSpriteSheet(ResourceManager::LoadTexture(spriteSheet))
{	
	pRender->SetFullScreen(true);

	for (int x = 0; x < m_Width; ++x)
	{
		for (int y = 0; y < m_Height; ++y)
		{
			m_Tiles[stringKey(x, y)] = nullptr;
		}
	}
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

void LevelComponent::AddTile(int x, int y, TileType tile, float rotation)
{
	const auto pTile = GetParent()->AddGameObject(stringKey(x,y));
	
	const auto pTrans = pTile->AddComponent(new TransformComponent(pTile));
	if (tile == TileType::wall)
	{
		pTile->AddComponent(new CollisionComponent(pTile, pTrans, float(m_TileSize.x), float(m_TileSize.y)));
	}
	else
	{
		const auto pRender = pTile->AddComponent(new RenderComponent(pTile, pTrans));
		
		pRender->SetSrcRect(GetSrcRect(tile));
		pRender->SetRotation(rotation);
		pRender->SetTexture(m_pSpriteSheet);
		pRender->SetPivot(m_TileSize / 2);
	}
	pTile->AddComponent(new TileComponent(pTile, x, y, tile, rotation));

	pTrans->SetPosition(GetPositionForTile(x, y));

	m_Tiles[stringKey(x, y)] = pTile;
}

void LevelComponent::GenerateWalls()
{
	for (int x = 0; x < m_Width; ++x)
	{
		for (int y = 0; y < m_Height; ++y)
		{
			const auto& string = stringKey(x, y);
			auto& pTile = m_Tiles[string];
			if (pTile)
				continue;

			pTile = GetParent()->AddGameObject(string);

			const auto pTrans = pTile->AddComponent(new TransformComponent(pTile));
			pTile->AddComponent(new CollisionComponent(pTile, pTrans, float(m_GridSize.x), float(m_GridSize.y)));

			pTrans->SetPosition(GetPositionForTile(x, y));
			pTile->AddComponent(new TileComponent(pTile, x, y, TileType::wall, 0));
		}
	}
}

std::vector<GameObject*> LevelComponent::GetNearbyTiles(glm::vec2 pos, float radius) const
{
	const auto pLevel = GetParent();

	std::vector<GameObject*> pNearbyTiles;
	for (const auto pTile : pLevel->GetGameObjects())
	{
		const auto& tilePos = pTile->GetComponent<TransformComponent>()->GetAbsolutePosition();

		const auto deltaVector = tilePos - pos;
		const auto dist = deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y;
		if (dist < radius * radius)
			pNearbyTiles.emplace_back(pTile);
	}
	return pNearbyTiles;
}

glm::vec2 LevelComponent::GetPositionForTile(int x, int y) const
{
	if (x < 0 || x >= m_Width)
		std::cout << "Tile location X " << x << " is out of bounds \n";

	if (y < 0 || y >= m_Height)
		std::cout << "Tile location Y " << y << " is out of bounds \n";


	glm::vec2 position{};

	const float maxSizeX = float(m_Width  * m_GridSize.x);
	const float maxSizeY = float(m_Height * m_GridSize.y);

	position.x += float(m_GridSize.x * x) - maxSizeX / 2;
	position.y += float(m_GridSize.y * y) - maxSizeY / 2;

	return position;
}



SDL_Rect LevelComponent::GetSrcRect(TileType tile) const
{
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_TileSize.x;
	srcRect.h = m_TileSize.y;

	switch (tile)
	{
	case TileType::end:
		srcRect.x = 0;
		break;
	case TileType::corner:
		srcRect.x = 32;
		break;
	case TileType::straight:
		srcRect.x = 64;
		break;
	case TileType::tPoint:
		srcRect.x = 96;
		break;
	case TileType::cross:
		srcRect.x = 128;
		break;
	}

	return srcRect;
}
