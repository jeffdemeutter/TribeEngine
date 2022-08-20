#include "GamePCH.h"
#include "InfoScreenComponent.h"
#include "GameTime.h"
#include "SceneManager.h"

InfoScreenComponent::InfoScreenComponent(GameObject* pGo, float time, const std::string& sceneToLoad)
	: Component(pGo)
	, m_MaxTime(time)
	, m_CurrentTime(0.f)
	, m_SceneToLoad(sceneToLoad)
{
}

void InfoScreenComponent::Update(GameContext& gc)
{
	m_CurrentTime += gc.pTime->GetDeltaTime();
	if (m_CurrentTime > m_MaxTime)
		gc.pSceneManager->ActivateScene(m_SceneToLoad);
}