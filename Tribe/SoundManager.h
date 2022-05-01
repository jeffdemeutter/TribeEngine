#pragma once
#include "Singleton.h"
class SoundManager : public Singleton<SoundManager>
{
public:
	virtual ~SoundManager() override = default;


private:
	SoundManager() = default;

};

