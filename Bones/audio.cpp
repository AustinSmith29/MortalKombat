#include "audio.h"

#include <iostream>

namespace bones
{
	AudioClip::AudioClip(const std::string& filename) : sound(Mix_LoadMUS(filename.c_str()))
	{
		if (!sound)
		{
			std::cout << "Could not load sound! " << Mix_GetError() << std::endl;
		}
	}

	void AudioClip::play()
	{
		if (Mix_PlayMusic(sound.get(), 1) == -1) {
			std::cout << "Can't play music! " << Mix_GetError() << std::endl;
		}
	}

	void AudioClip::restart()
	{
	}

	bool AudioClip::is_complete() const
	{
		return false;
	}
}