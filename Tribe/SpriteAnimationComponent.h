#pragma once
#include <unordered_map>

#include "BaseComponent.h"

class Texture2D;
class RenderComponent;
class SpriteAnimationComponent : public Component
{
public:
	struct Animation
	{
		SDL_Rect animationSource;
		int spriteSize = 16;
		int spriteCount = 1;
	};

	SpriteAnimationComponent(GameObject* go, RenderComponent* pRender, int framesPerSecond);
	~SpriteAnimationComponent() override;
	SpriteAnimationComponent(const SpriteAnimationComponent&) = delete;
	SpriteAnimationComponent(SpriteAnimationComponent&&) noexcept = delete;
	SpriteAnimationComponent& operator=(const SpriteAnimationComponent&) = delete;
	SpriteAnimationComponent& operator=(SpriteAnimationComponent&&) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void AddAnimation(int animationID, const SDL_Rect& src, int spriteSize, int spriteCount);
	void AddAnimation(int animationID, const Animation& animation);

	void SetActiveAnimation(int animationID);

private:
	std::unordered_map<int, Animation> m_Animations;
	int m_ActiveAnimationID;

	float m_TimeSinceLastFrame = 0.f;
	const int m_FramesPerSecond = 4;
	int m_CurrentFrame = 0;
	RenderComponent* m_pRenderComponent = nullptr;
};

