#include "TribePCH.h"
#include "EnemyComponent.h"
#include "EventManager.h"

EnemyComponent::EnemyComponent(GameObject* go)
	: Component(go)
{
	
}

void EnemyComponent::Update()
{
	
}

void EnemyComponent::Render() const
{
	
}

void EnemyComponent::KillEnemy() const
{
	ServiceLocator::GetEventManager()->Notify(m_pParent, EnemyDied);
}
