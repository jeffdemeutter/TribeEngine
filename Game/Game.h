#pragma once
#include <Tribe.h>

class Scene;

class Game final : public Tribe
{
public:
	Game() = default;
	~Game() override = default;
	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) noexcept = delete;

protected:
	virtual void LoadGame() const override;
};


