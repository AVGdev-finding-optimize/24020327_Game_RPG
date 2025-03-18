#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Core_System/Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false)) {
        std::cerr << "Error init game" << std::endl;
        return -1;
    }

    game.run();  // Chạy vòng lặp chính
    game.clean();
    return 0;
}