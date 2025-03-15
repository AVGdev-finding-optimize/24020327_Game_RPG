#include <SDL2/SDL.h>
#define SDL_MAIN_HANDLED

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();
    game->init("SDL2 Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    delete game;
    return 0;
}
