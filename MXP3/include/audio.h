#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_mixer.h>
#include <iostream>
#include <map>

//singleton audio
class _declspec(dllexport) Audio {
public:
	static Audio* getInstance();

	virtual void update();

	//standard playaudio. plays a WAV file ones on default values
	void playAudio(std::string filename);
	//playaudio function,
	//filename is the name of the file + the type.
	//loop 0 means it plays once. -1 is infinite loop, 
	//and all above 0 is the amount it will loop.
	//channel is the channel, -1 is the next channel available
	void playAudio(std::string filename, int loop, int channel);

	//pauses all audio
	void pauseAudio();
	//pauses audio. channel is the channel you're pausing
	void pauseAudio(int channel);
	//resumes all audio
	void resumeAudio();
	//resumes audio. channel is the channel you resume
	void resumeAudio(int channel);
	//changes the volume of all channels
	void volumeAudio(int volume);
	//changes the volume of the given channel
	void volumeAudio(int channel, int volume);

	//int volume equal to current volume level
	int volume;

	Mix_Chunk * getChunk(std::string filename);

private:
	static Audio* instance;

	Audio();
	virtual ~Audio();

	std::map<std::string, Mix_Chunk*> sounds;
};
