#pragma once
#include <thread>
#include <stack>
#include <mutex>
#include "Singleton.h"

enum SoundEvent
{
	playerHit,
	enemyHit,
	pointsChanged
};

class SoundManager final : public Singleton<SoundManager>
{
public:
	virtual ~SoundManager() override;
	
	static void LoadEffect(SoundEvent sound, const std::string& path);
	static void QueueEffect(SoundEvent sound);
	static void SetVolume(int volume);
	static void ChangeVolume(int delta);

private:
	friend class Singleton<SoundManager>;
	SoundManager();

	class SoundManagerSDLMixer;
	SoundManagerSDLMixer* m_pImpl = nullptr;

	std::thread m_Thr;
	std::stack<SoundEvent> m_Queue;
	std::mutex m_Mutex;
	bool m_Initialized = false;
};

