#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound {
public:
	void init();
	void loadSound(int channel_index);
	void playBackSound();
private:
    Mix_Chunk * SoundEffect[3];
    const int fall_sound=0;
    const int Point_sound=1;
    const int Button_sound=2;
    Mix_Music* Back_sound;
};

#endif // !SOUND_H
