#include "TribePCH.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent(GameObject* go)
	: Component(go)
{
	
}

void HealthComponent::LoseHealth()
{
	m_Health -= 1;
}

void HealthComponent::Kill()
{
	m_Health = 0;
}

void HealthComponent::Update()
{
}
