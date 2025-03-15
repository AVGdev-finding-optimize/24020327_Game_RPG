#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void clean();
    bool running() { return isRunning; }
    void render();

private:
    bool isRunning; 
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
