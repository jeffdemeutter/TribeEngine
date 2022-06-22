#pragma once

using namespace std::chrono;

class GameTime final
{
public:
	GameTime() = default;
	~GameTime() = default;
		
	float GetDeltaTime() const { return m_DeltaTime; }
	float GetTotalTime() const { return m_TotalTime; }
	int GetFps() const { return m_Fps; }

private:
	high_resolution_clock::time_point m_Start{};
	high_resolution_clock::time_point m_Last{};
	high_resolution_clock::time_point m_Current{};
	int m_Fps{ 0 };
	float m_DeltaTime{ 0.f };
	float m_TotalTime{ 0.f };

	static constexpr int m_MsPerFrame = 16; // 6 for 144 fps, 16 for 60 fps, 33 for 30 fps


	// funtions for the minigin class
	friend class Tribe;
	void Start();
	void Update();
	// this is the return type which is needed for the this_thread::sleep_for
	duration<long long, std::ratio<1, 1000000000>> GetSleepTime() const
	{
		return m_Current + milliseconds(m_MsPerFrame) - high_resolution_clock::now();
	}
};

