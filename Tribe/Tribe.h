#pragma once

struct SDL_Window;
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
	virtual void LoadGame() const = 0;
};
