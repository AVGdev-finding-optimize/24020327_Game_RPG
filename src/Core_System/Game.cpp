#include "Core_System/Game.h"
#include "Graphics_Rendering/Graphic.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Constructor
Game::Game() {
    isRunning = false;
}

// Destructor
Game::~Game() {
    clean();
}

// Hàm khởi tạo game
void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    if (!graphic.initSDL(width, height, title)) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        isRunning = false;
        return;
    }

    window = graphic.getWindow();
    renderer = graphic.getRenderer();

    if (!window || !renderer) {
        std::cerr << "Failed to create window or renderer!" << std::endl;
        isRunning = false;
        return;
    }

    isRunning = true;
}

// Hàm chạy vòng lặp game
void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

// Hàm xử lý sự kiện
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

// Hàm cập nhật trạng thái game
void Game::update() {
    // Viết logic cập nhật game ở đây
}

// Hàm render game
void Game::render() {
    graphic.prepareScene();
    // Vẽ hình ảnh ở đây
    graphic.presentScene();
}

// Hàm dọn dẹp tài nguyên game
void Game::clean() {
    graphic.quitSDL();
    isRunning = false;
}
