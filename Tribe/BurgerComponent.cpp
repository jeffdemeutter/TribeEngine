#include "TribePCH.h"
#include "BurgerComponent.h"
#include "RenderComponent.h"

#include "EventManager.h"

BurgerComponent::BurgerComponent(GameObject* go, RenderComponent* pRender, BurgerType type)
	: Component(go)
{
	InitBurgerType(pRender, type);
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

void BurgerComponent::InitBurgerType(RenderComponent* pRender, BurgerType type)
{
	switch (type)
	{
	case bunTop:
		pRender->SetSrcRect({ 112, 49, 31, 7 });
		break;
	case bunBottom:
		pRender->SetSrcRect({ 112, 58, 31, 6 });
		break;
	case cheese:
		pRender->SetSrcRect({ 114, 65, 28, 6 });
		break;
	case burger:
		pRender->SetSrcRect({ 114, 73, 28, 7 });
		break;
	case tomato:
		pRender->SetSrcRect({ 113, 81, 30, 7 });
		break;
	case salad:
		pRender->SetSrcRect({ 112, 89, 31, 7 });
		break;
	}
}
