#include "TribePCH.h"
#include "LevelComponent.h"
#include "RenderManager.h"

LevelComponent::LevelComponent(GameObject* go, int maxHeight)
	: Component(go)
	, m_Height(maxHeight)
{

}

void LevelComponent::Update()
{
	
}

void LevelComponent::Render() const
{
	
}

bool LevelComponent::GetPositionForCrossSection(const glm::ivec2& location, glm::vec3& position)
{
	if (location.x < 0 || location.x >= m_Width)
		throw "Invalid Crossection horizontal location";

	if (location.y < 0 || location.y >= m_Height)
		throw "Invalid Crossection vertical location";

	
	const SDL_Rect windowSize = RenderManager::GetWindowRect();

	// formula to calculate where the crossection should be rendered

	// remove the margin from both sides from window
	position.x = float(windowSize.w - m_HorizontalMargin * 2);
	position.y = float(windowSize.h - m_TopMargin - m_BottomMargin);
	// divide by levelWidth/Height and multiply with the location.x/y to find the position
	position.x /= m_Width;
	position.x *= location.x;
	position.y /= m_Height;
	position.y *= location.y;
	// add the margins back
	position.x += m_HorizontalMargin;
	position.y += m_TopMargin;

	return true;
}

