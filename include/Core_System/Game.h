#ifndef GAME_H
#define GAME_H

#include "Graphics_Rendering/Graphic.h"

class Game {
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Graphic graphic; // Sử dụng lớp Graphic để xử lý đồ họa

public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }
};

#endif