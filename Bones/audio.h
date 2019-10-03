#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL_mixer.h>
#include <string>
#include <memory>

namespace bones
{
	struct MixMusicDeleter {
		void operator()(Mix_Music* music)
		{
			Mix_FreeMusic(music);
		}
	};
	class AudioClip
	{
	public:
		AudioClip(const std::string& filename);

		void play();
		void restart();
		bool is_complete() const;
	private:
		std::unique_ptr<Mix_Music, MixMusicDeleter> sound;
	};
}
#endif