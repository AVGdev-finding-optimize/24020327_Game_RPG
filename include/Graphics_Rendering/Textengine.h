#ifndef TEXTENGINE_H
#define TEXTENGINE_H

#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include "Core_System/Const.h"

class TextEngine {
public:
    TextEngine(SDL_Renderer* renderer);
    ~TextEngine();

    bool loadFont(const std::string& fontPath, int fontSize);
    SDL_Texture* renderText(const std::string& text, SDL_Color color);
    
    void showText(const std::string& text, int x, int y, SDL_Color color, int alpha = 255);
    void showTextCenter(const std::string& text, SDL_Color color, int alpha = 255);

    void fadeInTextCenter(const std::string& text, SDL_Color color, int durationMs = 1000);
    void fadeOutTextCenter(const std::string& text, SDL_Color color, int durationMs = 1000);
    void fadeInText(const std::string& text, SDL_Color color, int x, int y, int durationMs = 1000);
    void fadeOutText(const std::string& text, SDL_Color color, int x, int y, int durationMs = 1000);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
};

#endif