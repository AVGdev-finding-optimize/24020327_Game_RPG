#include "Game.h"
#include <iostream>

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr) {}

Game::~Game() {
    clean();
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    // Khởi tạo SDL thông qua Graphic
    if (!graphic.initSDL(width, height, title)) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        isRunning = false;
        return;
    }

    // Lấy cửa sổ và renderer từ Graphic
    window = graphic.getWindow();
    renderer = graphic.getRenderer();
    
    // Kiểm tra xem cửa sổ và renderer có được tạo thành công không
    if (!window || !renderer) {
        std::cerr << "Failed to create window or renderer!" << std::endl;
        isRunning = false;
        return;
    }

    // Game bắt đầu chạy
    isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void Game::update() {
    // Update logic game tại đây
}

void Game::render() {
    graphic.prepareSence();
    // Vẽ đối tượng game tại đây
    graphic.presentSence();
}

void Game::clean() {
    graphic.quitSDL();
    std::cout << "Game cleaned!\n";
}
