#pragma once

enum SoundEvent
{
	hit,
	GameEnd,
	shot
};

class SoundManager final
{
public:
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager(SoundManager&&) noexcept = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager& operator=(SoundManager&&) noexcept = delete;
	
	void LoadEffect(SoundEvent sound, const std::string& path) const;
	void QueueEffect(SoundEvent sound) const;
	void SetVolume(int volume) const;
	void ChangeVolume(int delta) const;

private:
	class SoundManagerSDLMixer;
	SoundManagerSDLMixer* m_pImpl = nullptr;
};

