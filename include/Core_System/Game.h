#ifndef GAME_H
#define GAME_H

#include "Graphics_Rendering/Graphic.h"
#include "Entities/Player.h"
#include "Core_System/Const.h"

class Game {
private:
    bool isRunning;
    Graphic graphic;
    SDL_Texture* background;
    Player player;

public:
    Game();
    ~Game();
    
    void run();
    bool init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }
};

#endif