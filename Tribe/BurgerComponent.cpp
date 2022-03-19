#include "TribePCH.h"
#include "BurgerComponent.h"

#include "EventManager.h"

BurgerComponent::BurgerComponent(GameObject* go)
	: Component(go)
{
	
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
