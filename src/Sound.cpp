#include "sound.h"

void Sound::init() {
	 Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
    fall_sound = Mix_LoadMUS("obj/Sound/score++.wav");
	Point_sound =Mix_LoadMUS("obj/Sound/point.wav");
	Button_sound=Mix_LoadMUS("obj/Sound/button.wav");
	Back_sound=Mix_LoadMUS("obj/Sound/");
	}

void Sound::playPoint() {
      Mix_PlayMusic(fall_sound,-1);
}

void Sound::playBlock() {
  Mix_PlayMusic(Point_sound,-1);
}
void Sound::playButton(){
    Mix_PlayMusic(Button_sound,-1);
}
void Sound::playBackMusic(){
    Mix_PlayMusic(Back_sound,-1);
}
