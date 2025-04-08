#ifndef SOUND_H
#define SOUND_H

#include <SDL2_mixer/SDL_mixer.h>
#include <string>

class Sound {
public:
    Sound();
    ~Sound();

    bool loadMusic(const std::string& path);
    
    void play(int loops = -1);
    void playFadeIn(int loops = -1, int ms = 1000); 
    void pause();                              
    void resume();                              
    void stop();                                
    void fadeOut(int ms = 1000);                

    void setVolume(int volume);

    bool isPlaying() const;
    bool isPaused() const;

private:
    Mix_Music* music;
};

#endif