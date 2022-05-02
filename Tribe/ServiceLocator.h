#pragma once
#include "TribePCH.h"

class SoundManager;
class ServiceLocator final 
{
	static SoundManager* m_ServiceLocatorInstance;
public:
	static SoundManager* GetInstance() { return m_ServiceLocatorInstance; }
	static void SetInstance(SoundManager* pSoundManager) { m_ServiceLocatorInstance = pSoundManager; }
};