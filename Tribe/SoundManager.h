#pragma once
#include <thread>

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

	static void PlayEffect(SoundEvent sound);
	static void LoadEffect(SoundEvent sound, const std::string& path);


private:
	friend class Singleton<SoundManager>;
	SoundManager();

	class SoundManagerSDLMixer;
	SoundManagerSDLMixer* m_pImpl = nullptr;

	//std::thread m_Thr;
	float m_Audio = 1.f;
};

