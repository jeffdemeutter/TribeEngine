#pragma once
#include <Tribe.h>

class GameObject;
class Scene;

class Game final : public Tribe
{
public:
	Game() = default;
	~Game() override;
	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) noexcept = delete;

protected:
	virtual void LoadGame() override;

private:
	GameObject* m_pFps = nullptr;
	GameObject* m_pScore = nullptr;
	GameObject* m_pLivesObject = nullptr;
};


