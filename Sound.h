#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound {
public:
	void init();

	void playPoint();
	void playBlock();
	void playButton();
	void playBackMusic();
private:
    Mix_Chunk * SoundEffect[4];
    const int fall_sound=0;
    const int Point_sound=1;
    const int Button_sound=2;
    const int Back_sound=3;
};

#endif // !SOUND_H
