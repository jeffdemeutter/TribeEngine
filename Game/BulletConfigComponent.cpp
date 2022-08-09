#include "GamePCH.h"
#include "BulletConfigComponent.h"

BulletConfigComponent::BulletConfigComponent(GameObject* pGo)
	: Component(pGo)
	, m_SourceRect(SDL_Rect{ 0,0,32,32 })
	, m_Direction(1,0)
	, m_Pos(0,0)
	, m_Pivot(0,0)
	, m_Speed(10.f)	
{
	
}
