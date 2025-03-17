#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
class Graphic {
    private:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
    
    public:
        Graphic();
        ~Graphic();
        bool initSDL(int width, int height, const char* title);
        void quitSDL();
    
        SDL_Texture* loadTexture(const char* filename);
        SDL_Rect returnSize(SDL_Texture* texture , double ratio);
        void renderTexture(SDL_Texture* texture, int x = 0, int y = 0, int w = 100, int h = 100);
        
        void prepareScene();
        void presentScene();

    
        // Thêm getter để lấy window và renderer
        SDL_Window* getWindow() { return window; }
        SDL_Renderer* getRenderer() { return renderer; }
    };    

#endif