#include "TribePCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* go, int x, int y, int z)
	: Component(go)
	, m_Position( {x, y, z} )
{
}

TransformComponent::TransformComponent(GameObject* go, const glm::vec3& pos)
	: Component(go)
	, m_Position{ pos }
{
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;	
}

void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}
