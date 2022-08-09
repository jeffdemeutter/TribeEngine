#pragma once
#include <Component.h>

class BulletConfigComponent : public Component
{
public:
	BulletConfigComponent(GameObject* pGo);
	~BulletConfigComponent() override = default;
	BulletConfigComponent(const BulletConfigComponent&) = delete;
	BulletConfigComponent(BulletConfigComponent&&) noexcept = delete;
	BulletConfigComponent& operator=(const BulletConfigComponent&) = delete;
	BulletConfigComponent& operator=(BulletConfigComponent&&) noexcept = delete;

	virtual void Update(GameContext&) override {}
	virtual void Render() const override {}

	SDL_Rect GetSrcRect() const { return m_SourceRect; }
	void SetSrcRect(const SDL_Rect& srcRect) { m_SourceRect = srcRect; }
	glm::vec2 GetDirection() const { return m_Direction; }
	void SetDirection(const glm::vec2& dir) { m_Direction = dir; }
	glm::vec2 GetPos() const { return m_Pos; }
	void SetPos(const glm::vec2& pos) { m_Pos = pos; }
	glm::vec2 GetPivot() const { return m_Pivot; }
	void SetPivot(const glm::vec2& pivot) { m_Pivot = pivot; }
	float GetSpeed() const { return m_Speed; }
	void SetSpeed(float speed) { m_Speed = speed; }
	GameObject* GetSourceObject() const { return m_pSource; }
	void SetSourceObject(GameObject* pSource) { m_pSource = pSource; }

private:
	SDL_Rect m_SourceRect{0,0,32,32};
	glm::vec2 m_Direction{1.f, 0.f};
	glm::vec2 m_Pos{0.f, 0.f};
	glm::vec2 m_Pivot{ 0.f, 0.f};
	float m_Speed{10.f};

	GameObject* m_pSource = nullptr;
};

