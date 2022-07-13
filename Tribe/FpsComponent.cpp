#include "TribePCH.h"
#include "FpsComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "TextComponent.h"

FpsComponent::FpsComponent(GameObject* go, TextComponent* pTextComponent)
	: Component(go)
	, m_pTextComponent{ pTextComponent }
{
}

void FpsComponent::Update(GameContext& gc)
{
	m_pTextComponent->SetText(std::to_string(gc.pTime->GetFps()));
}
