#include "Sound.h"
#include <SDL_log.h>

Sound::Sound() {
    music = nullptr;
}

Sound::~Sound() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}

bool Sound::loadMusic(const std::string& path) {
    music = Mix_LoadMUS(path.c_str());
    if (!music) {
        SDL_Log("Failed to load music: %s", Mix_GetError());
        return false;
    }
    return true;
}

void Sound::play(int loops) {
    if (Mix_PlayMusic(music, loops) == -1) {
        SDL_Log("Failed to play music: %s", Mix_GetError());
    }
}

void Sound::playFadeIn(int loops, int ms) {
    if (Mix_FadeInMusic(music, loops, ms) == -1) {
        SDL_Log("Failed to fade in music: %s", Mix_GetError());
    }
}

void Sound::pause() {
    if (Mix_PlayingMusic() && !Mix_PausedMusic()) {
        Mix_PauseMusic();
    }
}

void Sound::resume() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void Sound::stop() {
    Mix_HaltMusic();
}

void Sound::fadeOut(int ms) {
    Mix_FadeOutMusic(ms);
}

void Sound::setVolume(int volume) {
    Mix_VolumeMusic(volume);
}

bool Sound::isPlaying() const {
    return Mix_PlayingMusic() == 1;
}

bool Sound::isPaused() const {
    return Mix_PausedMusic() == 1;
}