#include "TribePCH.h"
#include "Timer.h"

void Timer::StartImpl()
{
	m_Start = high_resolution_clock::now();
	m_Last = m_Start;
}

void Timer::UpdateImpl()
{
	// get current frame
	m_Current = high_resolution_clock::now();

	m_DeltaTime = duration<float>(m_Current - m_Last).count();
	m_TotalTime = duration<float>(m_Current - m_Start).count();

	// calculate the fps
	m_Fps = int(1.f / m_DeltaTime);

	// update the last frames time
	m_Last = m_Current;
}

