#ifndef AUDIO_H
#define AUDIO_H

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Volume Control
	void ControlVolume(int vol);
	void ControlMUSVolume(int vol);
	void ControlSFXVolume(int vol);

private:

	_Mix_Music *music = NULL;
	std::list<Mix_Chunk*>	fx;
};

#endif // AUDIO_H