#ifndef TEXTENGINE_H
#define TEXTENGINE_H

#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class TextEngine {
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    

public:
    TextEngine(SDL_Renderer* renderer);
    ~TextEngine();
    
    SDL_Texture* renderText(const std::string& text, SDL_Color color);
    bool loadFont(const std::string& fontPath, int fontSize);
    void showText(const std::string& text, int x, int y, SDL_Color color);

};

#endif