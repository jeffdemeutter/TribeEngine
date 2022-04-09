#include "TribePCH.h"
#include "CrossComponent.h"

#include "LevelComponent.h"
#include "TransformComponent.h"

CrossComponent::CrossComponent(GameObject* go, LevelComponent* pLevel, TransformComponent* pTransform, const glm::ivec2& location)
	: Component(go)
{
	if (glm::vec3 pos; pLevel->GetPositionForCrossSection(location, pos))
		pTransform->SetPosition(pos);
	
}

void CrossComponent::Update()
{
	
}

void CrossComponent::Render() const
{
	
}
