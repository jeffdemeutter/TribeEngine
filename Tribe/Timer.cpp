#include "TribePCH.h"
#include "Timer.h"

void Timer::Start()
{
	Instance().m_Start = high_resolution_clock::now();
	Instance().m_Last = Instance().m_Start;
}

void Timer::Update()
{
	// get current frame
	Instance().m_Current = high_resolution_clock::now();

	Instance().m_DeltaTime = duration<float>(Instance().m_Current - Instance().m_Last).count();
	Instance().m_TotalTime = duration<float>(Instance().m_Current - Instance().m_Start).count();

	// calculate the fps
	Instance().m_Fps = int(1.f / Instance().m_DeltaTime);

	// update the last frames time
	Instance().m_Last = Instance().m_Current;
}

