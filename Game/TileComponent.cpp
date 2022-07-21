#include "GamePCH.h"
#include "TileComponent.h"

#include "GameTime.h"
#include "LevelComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

TileComponent::TileComponent(GameObject* go, int x, int y, TileType tile, float rotation)
	: Component(go)
	, m_Location(x, y)
	, m_Type(tile)
	, m_Rotation(rotation)
{
}

