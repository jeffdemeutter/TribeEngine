#include "GamePCH.h"
#include "ButtonComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "InputManager.h"


ButtonComponent::ButtonComponent(GameObject* pGo, CollisionComponent* pCollision, Command* pCommand)
	: Component(pGo)
	, m_pCollision(pCollision)
	, m_pCommand(pCommand)
{
	
}

ButtonComponent::~ButtonComponent()
{
	m_pCollision = nullptr;

	delete m_pCommand;
	m_pCommand = nullptr;
}

void ButtonComponent::CheckIfClicked() const
{
	if (!GetParent()->IsActive())
		return;

	const auto& pos = InputManager::GetMousePosition();

	if (m_pCollision->CheckCollision(pos))
	{
		m_pCommand->Execute();
	}
}
