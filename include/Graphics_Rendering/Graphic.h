#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

class Graphic {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Graphic();
    ~Graphic();
    
    bool initSDL(int width, int height, const char* title);
    
    SDL_Texture* loadTexture(const std::string& filename);
    void renderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    
    void prepareScene();
    void presentScene();
    
    SDL_Renderer* getRenderer() { return renderer; }
    SDL_Window* getWindow() { return window; }
};

#endif