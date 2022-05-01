#include "TribePCH.h"
#include "SoundManager.h"

#include <unordered_map>

#include "SDL2/SDL_mixer.h"

class SoundManager::SoundManagerSDLMixer
{
public:
	SoundManagerSDLMixer();
	~SoundManagerSDLMixer();

	void Run();
	void LoadEffect(SoundEvent sound, const std::string& path);
	void ChangeVolume(int volume);

private:
	std::unordered_map<SoundEvent, Mix_Chunk*> m_Effects;
};

SoundManager::SoundManagerSDLMixer::SoundManagerSDLMixer()
{
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 |	MIX_INIT_OGG);

	// use of 22050 frequency, documentation of sdl_mixer suggests this for games, it will use less cpu power like this
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 4, 1024) == -1)
		throw "Failed to openAudio\n";
}

SoundManager::SoundManagerSDLMixer::~SoundManagerSDLMixer()
{
	for (const auto& effect : m_Effects)
		SafeDelete(effect.second);

	m_Effects.clear();

	Mix_CloseAudio();
	Mix_Quit();
}

void SoundManager::SoundManagerSDLMixer::Run()
{
	while (Instance().m_Initialized)
	{
		if (Instance().m_Queue.empty())
			continue;

		Instance().m_Mutex.lock();

		Mix_PlayChannel(-1, m_Effects.at(Instance().m_Queue.top()), 0);
		Instance().m_Queue.pop();

		Instance().m_Mutex.unlock();
	}
}

void SoundManager::SoundManagerSDLMixer::LoadEffect(SoundEvent sound, const std::string& path)
{
	if (auto pEffect = Mix_LoadWAV(path.c_str()))
		m_Effects[sound] = pEffect;
	else
		throw "Effect " + path + " failed to load";
}

void SoundManager::SoundManagerSDLMixer::ChangeVolume(int volume)
{
	Mix_Volume(-1, volume);
}


SoundManager::SoundManager()
	: m_pImpl{ new SoundManagerSDLMixer() }
{
	m_Initialized = true;
	m_Thr = std::thread{ [&] { m_pImpl->Run(); } };
}

SoundManager::~SoundManager()
{
	m_Initialized = false;
	m_Thr.join();
	SafeDelete(m_pImpl);
}

void SoundManager::LoadEffect(SoundEvent sound, const std::string& path)
{
	Instance().m_pImpl->LoadEffect(sound, path);
}

void SoundManager::QueueEffect(SoundEvent sound)
{
	Instance().m_Mutex.lock();
	Instance().m_Queue.push(sound);
	Instance().m_Mutex.unlock();
}

void SoundManager::ChangeVolume(int volume)
{
	Instance().m_pImpl->ChangeVolume(volume);
}
