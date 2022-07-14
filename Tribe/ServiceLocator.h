#pragma once
#include "TribePCH.h"

class SoundManager;
class EventManager;
class ServiceLocator final 
{
// Soundmanager serviceLocator
// ===========================
	static SoundManager* m_pSoundManager;
public:
	static SoundManager* GetSoundManager() { return m_pSoundManager; }
	static void SetSoundManager(SoundManager* pSoundManager) {
		m_pSoundManager = pSoundManager; }


// EventManager serviceLocator
// ===========================
private:
	static EventManager* m_pEventManager;
public:
	static EventManager* GetEventManager() { return m_pEventManager; }
	static void SetEventManager(EventManager* pService) {
		m_pEventManager = pService; }

};