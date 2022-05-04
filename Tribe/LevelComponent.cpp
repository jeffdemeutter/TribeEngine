#include "TribePCH.h"
#include "LevelComponent.h"
#include "RenderManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Components.h"

LevelComponent::LevelComponent(GameObject* go, int maxHeight, const std::string& tileSprite, const glm::ivec2& tileSize)
	: Component(go)
	, m_WindowSize(RenderManager::GetWindowRect())
	, m_Height(maxHeight)
	, m_TileSize(tileSize)
	, m_pTexture(ResourceManager::LoadTexture(tileSprite)) {
}

void LevelComponent::Update()
{
	
}

void LevelComponent::Render() const
{
	
}

TileComponent* LevelComponent::AddTile(int x, int y, TileType tile)
{
	TileComponent* pTile;

	const auto go = new GameObject(std::to_string(x) + " - " + std::to_string(y));
	{
		const auto pTrans = go->AddComponent(new TransformComponent(go));
		const auto pRender = go->AddComponent(new RenderComponent(go, pTrans));
		pTile = go->AddComponent(new TileComponent(go, x, y, this, pTrans, pRender, tile));
	}
	GetParent()->AddChild(go);

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
	position.x = float(m_WindowSize.w );
	position.y = float(m_WindowSize.h );
	// divide by levelWidth/Height and multiply with the location.x/y to find the position
	position.x /= float(m_Width);
	position.x += float(m_TileSize.x * x * g_PixelScale);

	position.y /= float(m_Height);
	position.y += float(m_TileSize.y * y * g_PixelScale);
	// add the margins back
	//position.x += float(m_HorizontalMargin);
	//position.y += float(m_TopMargin);

	return true;
}

