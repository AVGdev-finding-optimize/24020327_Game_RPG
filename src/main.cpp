#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Core_System/Game.h"

int SDL_main(int argc, char* argv[]) {
    Game* game = new Game();

    if (!game->initSDL(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false)) {
        std::cerr << "Failed to initialize game." << std::endl;
        delete game;
        return -1;
    }
    /* game->intro(); */
    game->foreverLoop();

    delete game;
    return 0;
}