#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

class Tribe;
class Timer final : public Singleton<Timer>
{
public:
	~Timer() override = default;
		
	static float GetDeltaTime() { return Instance().m_DeltaTime; }
	static float GetTotalTime() { return Instance().m_TotalTime; }
	static int GetFps() { return Instance().m_Fps; }

private:
	friend class Singleton<Timer>;
	Timer() = default;

	high_resolution_clock::time_point m_Start{};
	high_resolution_clock::time_point m_Last{};
	high_resolution_clock::time_point m_Current{};
	int m_Fps{ 0 };
	float m_DeltaTime{ 0.f };
	float m_TotalTime{ 0.f };

	static constexpr int m_MsPerFrame = 16; // 6 for 144 fps, 16 for 60 fps, 33 for 30 fps


	// funtions for the minigin class
	friend class Tribe;
	static void Start();
	static void Update();
	// this is the return type which is needed for the this_thread::sleep_for
	static duration<long long, std::ratio<1,1000000000>> GetSleepTime()
	{
		return Instance().m_Current + milliseconds(m_MsPerFrame) - high_resolution_clock::now();
	}
};


