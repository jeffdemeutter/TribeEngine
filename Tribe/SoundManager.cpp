#include "TribePCH.h"
#include "SoundManager.h"

#include <unordered_map>
#include <thread>
#include <queue>
#include <mutex>

#include "SDL2/SDL_mixer.h"

class SoundManager::SoundManagerSDLMixer
{
public:
	SoundManagerSDLMixer();
	~SoundManagerSDLMixer();

	void Run();
	void LoadEffect(SoundEvent sound, const std::string& path);
	void QueueEffect(SoundEvent sound);
	void SetVolume(int volume);
	void ChangeVolume(int delta);

private:
	std::unordered_map<SoundEvent, Mix_Chunk*> m_Effects;

	int m_Volume = 100;

	std::thread m_Thr;
	std::queue<SoundEvent> m_Queue;
	std::mutex m_Mutex;
	bool m_Initialized = false;
};

SoundManager::SoundManagerSDLMixer::SoundManagerSDLMixer()
{
	Mix_Init( MIX_INIT_MOD );

	// use of 22050 frequency, documentation of sdl_mixer suggests this for games, it will use less cpu power like this
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 4, 1024) == -1)
		throw "Failed to openAudio\n";

	m_Initialized = true;

	m_Thr = std::thread{ [&] { Run(); } };
}

SoundManager::SoundManagerSDLMixer::~SoundManagerSDLMixer()
{
	m_Initialized = false;

	for (const auto& effect : m_Effects)
		SafeDelete(effect.second);

	m_Effects.clear();

	Mix_CloseAudio();
	Mix_Quit();
}

void SoundManager::SoundManagerSDLMixer::Run()
{
	while (m_Initialized)
	{
		if (m_Queue.empty())
			continue;

		m_Mutex.lock();

		Mix_PlayChannel(-1, m_Effects.at(m_Queue.front()), 0);
		m_Queue.pop();

		m_Mutex.unlock();
	}
}

void SoundManager::SoundManagerSDLMixer::LoadEffect(SoundEvent sound, const std::string& path)
{
	if (auto pEffect = Mix_LoadWAV(path.c_str()))
		m_Effects[sound] = pEffect;
	else
		throw "Effect " + path + " failed to load";
}

void SoundManager::SoundManagerSDLMixer::QueueEffect(SoundEvent sound)
{
	m_Mutex.lock();
	m_Queue.push(sound);
	m_Mutex.unlock();
}

void SoundManager::SoundManagerSDLMixer::SetVolume(int volume)
{
	m_Volume = volume;
	Mix_Volume(-1, m_Volume);
}

void SoundManager::SoundManagerSDLMixer::ChangeVolume(int delta)
{
	m_Volume += delta;
	Mix_Volume(-1, m_Volume);
}


SoundManager::SoundManager()
	: m_pImpl{ new SoundManagerSDLMixer() }
{
}

SoundManager::~SoundManager()
{
	SafeDelete(m_pImpl);
}

void SoundManager::LoadEffect(SoundEvent sound, const std::string& path) const
{
	m_pImpl->LoadEffect(sound, path);
}

void SoundManager::QueueEffect(SoundEvent sound) const
{
	m_pImpl->QueueEffect(sound);
}

void SoundManager::SetVolume(int volume) const
{
	m_pImpl->SetVolume(volume);
}

void SoundManager::ChangeVolume(int delta) const
{
	m_pImpl->ChangeVolume(delta);
}
