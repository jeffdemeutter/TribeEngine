#include "TribePCH.h"
#include "GameTime.h"

void GameTime::Start()
{
	m_Start = high_resolution_clock::now();
	m_Last = m_Start;
}

void GameTime::Update()
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

