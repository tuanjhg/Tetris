#include "sound.h"

void Sound::init() {
	 Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
    SoundEffect[fall_sound] = Mix_LoadWAV("obj/Sound/score++.wav");
	SoundEffect[Point_sound] =Mix_LoadWAV("obj/Sound/point.wav");
	SoundEffect[Button_sound]=Mix_LoadWAV("obj/Sound/button.wav");
	Back_sound=Mix_LoadMUS("obj/Sound/backsound.mp3");
	}

void Sound::loadSound(int channel_index) {
    if(channel_index==0)
     Mix_PlayChannel(channel_index, SoundEffect[fall_sound],0);
    else if(channel_index==1){
     Mix_PlayChannel(channel_index, SoundEffect[Point_sound],0);
    }else{
     Mix_PlayChannel(channel_index, SoundEffect[Button_sound],0);
}
}
void Sound::playBackSound(){
       Mix_PlayMusic(Back_sound,-1);
}
