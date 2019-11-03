#include "audio.h"

#include <iostream>

namespace bones
{
	AudioClip::AudioClip(const std::string& filename) : sound(Mix_LoadWAV(filename.c_str()))
	{
		if (!sound)
		{
			std::cout << "Could not load sound! " << Mix_GetError() << std::endl;
		}
		else
		{
			std::cout << "Sound loaded!" << std::endl;
		}
	}

	void AudioClip::play(int loops)
	{
		if (Mix_PlayChannel(-1, sound.get(), loops) == -1) {
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