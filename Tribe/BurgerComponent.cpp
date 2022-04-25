#include "TribePCH.h"
#include "BurgerComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "EventManager.h"

BurgerComponent::BurgerComponent(GameObject* go, RenderComponent* pRender, TransformComponent* pTrans, BurgerType type, glm::vec3 position)
	: Component(go)
{
	constexpr static int yOffset = -3;

	const auto& srcRect = InitBurgerType(type);
	pRender->SetSrcRect(srcRect);

	// set the position with center
	position.x -= srcRect.w / 2 * g_PixelScale;
	position.y -= srcRect.h / 2 * g_PixelScale;

	// add an offset to make it look like it's on top of the platform
	position.y += yOffset * g_PixelScale;

	pTrans->SetPosition(position);
}

void BurgerComponent::Update()
{
	
}

void BurgerComponent::Render() const
{
	
}

void BurgerComponent::DropBurger() const
{
	EventManager::Notify(m_pParent, BurgerDrop);
}

const SDL_Rect& BurgerComponent::InitBurgerType(BurgerType type)
{
	static constexpr SDL_Rect srcBunTop		{ 112, 49, 31, 7 };
	static constexpr SDL_Rect srcBunBottom	{ 112, 58, 31, 6 };
	static constexpr SDL_Rect srcCheese		{ 114, 65, 28, 6 };
	static constexpr SDL_Rect srcBurger		{ 114, 73, 28, 7 };
	static constexpr SDL_Rect srcTomato		{ 113, 81, 30, 7 };
	static constexpr SDL_Rect srcSalad		{ 112, 89, 31, 7 };

	switch (type)
	{
	case bunTop:
		return srcBunTop;
	case bunBottom:
		return srcBunBottom;
	case cheese:
		return srcCheese;
	case burger:
		return srcBurger;
	case tomato:
		return srcTomato;
	case salad:
		return srcSalad;
	}

	// default to just prevent warning/error
	return srcBunTop;
}
