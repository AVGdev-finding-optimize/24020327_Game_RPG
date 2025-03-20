#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include "Core_System/Const.h"

class Graphic {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Graphic();
    ~Graphic();

    bool initSDL(int width, int height, const char* title);
    SDL_Texture* loadTexture(const std::string& filePath);
    void renderTextureKeepRatio(SDL_Texture* texture, int x, int y, int maxWidth, int maxHeight);
    void renderBackground(SDL_Texture* texture, int x, int y);
    void prepareScene();
    void presentScene();

    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
};

#endif