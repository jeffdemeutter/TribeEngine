#pragma once
#include "Structs.h"

class Tribe
{
public:
	Tribe() = default;
	virtual ~Tribe() = default;
	Tribe(const Tribe&) = delete;
	Tribe(Tribe&&) noexcept = delete;
	Tribe& operator=(const Tribe&) = delete;
	Tribe& operator=(Tribe&&) noexcept = delete;

	void Run();

protected:
	virtual void LoadGame() = 0;

	GameContext m_GameContext{};
};

