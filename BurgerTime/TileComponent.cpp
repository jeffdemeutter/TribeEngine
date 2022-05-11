#include "TribePCH.h"
#include "TileComponent.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include "BurgerComponent.h"

TileComponent::TileComponent(GameObject* go, int x, int y, LevelComponent* pLevel, TransformComponent* pTransform, RenderComponent* pRender, TileType tile)
	: Component(go)
	, m_pTransform(pTransform)
	, m_pLevel(pLevel)
{
	glm::vec3 pos;
	if (pLevel->GetPositionForTile(x, y, pos))
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

glm::vec3 TileComponent::GetBurgerPosition() const
{
	auto pos = m_pTransform->GetPosition();
	auto size = m_pLevel->GetTileSize();
	size *= g_PixelScale;

	return { pos.x + size.x / 2,pos.y + size.y / 2, 1 };
}

void TileComponent::AddBurgerObject(BurgerComponent::BurgerType type) const
{
	auto* go = new GameObject("Bun Top 1");
	{
		auto pTransform = go->AddComponent(new TransformComponent(go));
		auto pRender = go->AddComponent(new RenderComponent(go, pTransform, "spritesheet.png"));

		go->AddComponent(new BurgerComponent(go, pRender, pTransform, type, GetBurgerPosition()));
	}
	GetParent()->AddChild(go);
}

glm::vec3 TileComponent::GetPosition() const
{
	auto pos = m_pTransform->GetPosition();
	pos.x += m_pPawnOffsets.x * g_PixelScale;
	pos.y += m_pPawnOffsets.y * g_PixelScale;
	pos.z = 1;

	return pos;
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


