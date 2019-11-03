#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL_mixer.h>
#include <string>
#include <memory>

namespace bones
{
	struct MixChunkDeleter {
		void operator()(Mix_Chunk* sound)
		{
			Mix_FreeChunk(sound);
		}
	};
	class AudioClip
	{
	public:
		AudioClip(const std::string& filename);

		void play(int loops=0);
		void restart();
		bool is_complete() const;
	private:
		std::unique_ptr<Mix_Chunk, MixChunkDeleter> sound;
	};
}
#endif