#include "Core_System/Game.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

Uint32 frameStart;
int frameTime;

// Constructor
Game::Game() : player(graphic) {
    isRunning = false;
}

// Destructor
Game::~Game() {
    clean();
}

// Hàm kiểm tra khởi tạo game
bool Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    std::cout << "Initializing SDL...\n";

    if (!graphic.initSDL(width, height, title)) {
        std::cerr << "Error init SDL" << std::endl;
        isRunning = false;
        return false;
    }

    std::cout << "SDL Initialized!\n";
    
    background = graphic.loadTexture(BACKGROUND_PATH);
    if (!background) {
        std::cerr << "Error loading background" << std::endl;
        isRunning = false;
        return false;
    }

    // Khởi tạo player
    player.init(graphic);

    std::cout << "Background loaded!\n";
    isRunning = true;
    return true;
}

// Hàm chạy vòng lặp game
void Game::run() {
    std::cout << "Game is running...\n";
    while (isRunning) {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}

// Hàm xử lý sự kiện
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        player.handleInput(event);
    }
}

// Hàm cập nhật trạng thái game
void Game::update() {
    player.update();
}

// Hàm render game
void Game::render() {
    graphic.prepareScene();
    graphic.renderTexture(background, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    player.render(graphic);
    graphic.presentScene();
}

// Hàm dọn dẹp tài nguyên game
void Game::clean() {
    std::cout << "Cleaning up game...\n";

    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    isRunning = false;
}