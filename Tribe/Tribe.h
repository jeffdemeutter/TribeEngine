#pragma once

struct SDL_Window;
class Tribe final
{
public:
	Tribe() = default;
	~Tribe() = default;
	Tribe(const Tribe&) = delete;
	Tribe(Tribe&&) noexcept = delete;
	Tribe& operator=(const Tribe&) = delete;
	Tribe& operator=(Tribe&&) noexcept = delete;

	void Run();

private:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
};
