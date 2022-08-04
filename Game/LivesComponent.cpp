#include "GamePCH.h"
#include "LivesComponent.h"

LivesComponent::LivesComponent(GameObject* pGo, int lives)
	: Component(pGo)
	, m_Lives(lives)
{
	
}

void LivesComponent::Update(GameContext&)
{
	
}

