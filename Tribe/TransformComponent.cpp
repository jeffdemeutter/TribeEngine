#include "TribePCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent(GameObject* pGo, float x, float y, float depth)
	: Component(pGo)
	, m_Position(x, y)
	, m_Depth(depth)
{
}

TransformComponent::TransformComponent(GameObject* pGo, const glm::vec2& pos, float depth)
	: Component(pGo)
	, m_Position(pos)
	, m_Depth(depth)
{
}
