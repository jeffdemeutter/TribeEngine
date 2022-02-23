#include "TribePCH.h"
#include "FpsComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"

FpsComponent::FpsComponent(GameObject* go, TextComponent* pTextComponent)
	: Component(go)
	, m_pTextComponent{ pTextComponent }
{
}

void FpsComponent::Update()
{
	m_pTextComponent->SetText(std::to_string(Timer::GetFps()));
}
