#include "TribePCH.h"
#include "TileComponent.h"

#include "LevelComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

TileComponent::TileComponent(GameObject* go, LevelComponent* pLevel, TransformComponent* pTransform, const glm::ivec2& location, RenderComponent* pRender, TileType tile)
	: Component(go)
{
	glm::vec3 pos;
	if (pLevel->GetPositionForTile(location, pos))
		pTransform->SetPosition(pos);

	pRender->SetTexture(pLevel->GetTexture());
	pRender->SetSrcRect(GetCorrespondingSrcRect(tile, pLevel));
}

void TileComponent::Update()
{
	
}

void TileComponent::Render() const
{
	
}

// turned of this warning to use the enum as a bitflag
#pragma warning( disable : 4063 )

SDL_Rect TileComponent::GetCorrespondingSrcRect(TileType tile, LevelComponent* pLevel)
{
	// this corresponds to the default tilesprites.png tileset. You can swap out the spritesheet with another one, with all the tiletypes in the same spot (even with a different resolution), and this will work aswell

	auto tileSize = pLevel->GetTileSize();
	SDL_Rect srcRect;
	srcRect.x = tileSize.x;
	srcRect.y = tileSize.y;
	srcRect.w = tileSize.x;
	srcRect.h = tileSize.y;

	
	// check if it is just a ladder
	if (tile == TileType::ladder)
	{
		srcRect.x *= 3;
		srcRect.y *= 4;
		return srcRect;
	}

	// check x of the tileSet
	// in this case its bottom and top
	if ((tile == TileType::bottom) && (tile == TileType::top))
		srcRect.x *= 2;
	else if (tile == TileType::bottom)
		srcRect.x *= 0;
	else if (tile == TileType::top)
		srcRect.x *= 1;
	else
		srcRect.x *= 3;

	// check y of the tileSet
	// in this case its left, right, platform or none
	if (tile == TileType::platform)
		srcRect.y *= 0;
	else if ((tile == TileType::left) && (tile == TileType::right))
		srcRect.y *= 1;
	else if (tile == TileType::left)
		srcRect.y *= 2;
	else if (tile == TileType::right)
		srcRect.y *= 3;
	else
		srcRect.y *= 4;
	

	return srcRect;
}


