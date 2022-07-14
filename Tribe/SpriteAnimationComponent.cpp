#include "TribePCH.h"
#include "SpriteAnimationComponent.h"

#include "GameTime.h"
#include "RenderComponent.h"


SpriteAnimationComponent::SpriteAnimationComponent(GameObject* go, RenderComponent* pRender, int framesPerSecond)
	: Component(go)
	, m_FramesPerSecond{framesPerSecond}
	, m_pRenderComponent{pRender}
{
	
}

SpriteAnimationComponent::~SpriteAnimationComponent()
{
	m_pRenderComponent = nullptr;
}

void SpriteAnimationComponent::Update(GameContext& gc)
{
	 m_TimeSinceLastFrame += gc.pTime->GetDeltaTime();
	 const auto& activeAnim = m_Animations[m_ActiveAnimationID];

	 if ((1.f / float(m_FramesPerSecond)) > m_TimeSinceLastFrame)
		 return;
	
	// intentional copy
	auto rect = activeAnim.animationSource;
	rect.w /= activeAnim.spriteCount;
	rect.x += activeAnim.spriteSize * m_CurrentFrame;
	m_pRenderComponent->SetSrcRect(rect);

	++m_CurrentFrame;
	m_CurrentFrame = m_CurrentFrame % activeAnim.spriteCount;
	m_TimeSinceLastFrame = 0.f;
}

void SpriteAnimationComponent::AddAnimation(int action, const SDL_Rect& src, int spriteSize,
	int spriteCount)
{
	Animation anim{};
		anim.animationSource = src;
		anim.spriteCount = spriteCount;
		anim.spriteSize = spriteSize;
	AddAnimation(action, anim);
}

void SpriteAnimationComponent::AddAnimation(int animationID, const Animation& animation)
{
	m_Animations[animationID] = animation;
}

void SpriteAnimationComponent::SetActiveAnimation(int animationID)
{
	m_ActiveAnimationID = animationID;

	const auto& activeAnim = m_Animations[m_ActiveAnimationID];

	if (activeAnim.spriteCount <= m_CurrentFrame)
		m_CurrentFrame = 0;
}
