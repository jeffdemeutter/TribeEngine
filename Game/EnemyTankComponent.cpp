#include "GamePCH.h"
#include "EnemyTankComponent.h"

#include "EventManager.h"
#include "GameObject.h"
#include "GameTime.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
#include "TransformComponent.h"
#include "Raycast.h"
#include "LevelComponent.h"

EnemyTankComponent::EnemyTankComponent(GameObject* pGo, TransformComponent* pTrans, RenderComponent* pRender, CollisionComponent* pCollision, MovementComponent* pMovement, LevelComponent* pLevel, TankType tankType, int lives)
	: Component(pGo)
	, m_pTransform(pTrans)
	, m_pRender(pRender)
	, m_pCollision(pCollision)
	, m_pMovement(pMovement)
	, m_pLevel(pLevel)
	, m_Lives(lives)
	, m_Type(tankType)
{
	switch (m_Type)
	{
	case TankType::blueTank:
		m_pRender->SetSrcRect(SDL_Rect{ 00,96,32,32 });
		m_pMovement->SetMovementSpeed(125);
		break;
	case TankType::recognizer:
		m_pRender->SetSrcRect(SDL_Rect{ 64,64,32,32 });
		m_pMovement->SetMovementSpeed(250);
		break;
	}

	m_pRender->SetCenter({ 16,16 });
	m_pRender->SetPivot({ 16,16 });
}

EnemyTankComponent::~EnemyTankComponent()
{
	m_pTarget = nullptr;
}

void EnemyTankComponent::Update(GameContext& )
{
	MovementAI();
}

void EnemyTankComponent::MovementAI()
{

}

void EnemyTankComponent::Hit()
{
	--m_Lives;
	if (m_Lives > 0)
		return;

	

	const auto pTank = GetParent();

	if (m_Type == TankType::blueTank)
		ServiceLocator::GetEventManager()->Notify(pTank, BlueTankDied);
	else if (m_Type == TankType::recognizer)
		ServiceLocator::GetEventManager()->Notify(pTank, RedRecognizerDied);

	pTank->Remove();
}