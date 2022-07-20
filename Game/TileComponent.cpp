#include "GamePCH.h"
#include "TileComponent.h"

#include "GameTime.h"
#include "LevelComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

TileComponent::TileComponent(GameObject* go, int x, int y, LevelComponent* pLevel, TransformComponent* pTransform, RenderComponent* pRender, TileType tile, float rotation)
	: Component(go)
	, m_pTransform(pTransform)
	, m_pLevel(pLevel)
{
	glm::vec3 pos;
	if (pLevel->GetPositionForTile(x, y, pos))
		pTransform->SetPosition(pos);


	auto tileSize = pLevel->GetTileSize();
	SDL_Rect srcRect;
	srcRect.y = 0;
	srcRect.w = tileSize.x;
	srcRect.h = tileSize.y;

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

	pRender->SetSrcRect(srcRect);
	pRender->SetRotation(rotation);
	pRender->SetTexture(pLevel->GetTexture());
	pRender->SetPivot(tileSize / 2);
	pRender->SetCenter(tileSize / 2);
}

