#include "TribePCH.h"
#include "Timer.h"

void Timer::Start()
{
	Get().m_Start = high_resolution_clock::now();
	Get().m_Last = Get().m_Start;
}

void Timer::Update()
{
	// get current frame
	Get().m_Current = high_resolution_clock::now();

	Get().m_DeltaTime = duration<float>(Get().m_Current - Get().m_Last).count();
	Get().m_TotalTime = duration<float>(Get().m_Current - Get().m_Start).count();

	// calculate the fps
	Get().m_Fps = int(1.f / Get().m_DeltaTime);

	// update the last frames time
	Get().m_Last = Get().m_Current;
}

