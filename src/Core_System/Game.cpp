#include "Core_System/Game.h"
#include "Graphics_Rendering/Graphic.h"
#include <iostream>
#include "Const.h"

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
    
    window = graphic.getWindow();
    renderer = graphic.getRenderer();

    std::cout << "Loading background...\n";
    
    BackgroundTexture = graphic.loadTexture(BACKGROUND_PATH);
    if (BackgroundTexture == nullptr) {
        std::cerr << "Error load background" << std::endl;
        isRunning = false;
        return false;
    }

    PlayerTexture = graphic.loadTexture(PLAYER_SPRITE_PATH);
    if (PlayerTexture == nullptr) {
        std::cerr << "Error load player sprite" << std::endl;
        isRunning = false;
        return false;
    }

    std::cout << "Background loaded!\n";
    isRunning = true;
    return true;
}

// Hàm chạy vòng lặp game
void Game::run() {
    std::cout << "Game is running...\n";
    while (isRunning) {
        frameStart = SDL_GetTicks();  // Lấy thời gian bắt đầu frame
        
        handleEvents();
        update();
        render();

        // Giới hạn FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);  // Đợi cho đủ thời gian frame
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
        else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_EXPOSED) {
                render();  // Vẽ lại ngay khi cửa sổ được kéo
            }
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
    graphic.renderTexture(BackgroundTexture, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    graphic.renderTexture(PlayerTexture, 100, 100, PLAYER_WIDTH, PLAYER_HEIGHT);
    graphic.presentScene();
}

// Hàm dọn dẹp tài nguyên game
void Game::clean() {
    std::cout << "Cleaning up game...\n";
    if (BackgroundTexture) {
        SDL_DestroyTexture(BackgroundTexture);
        BackgroundTexture = nullptr;
    }
    if (PlayerTexture) {
        SDL_DestroyTexture(PlayerTexture);
        PlayerTexture = nullptr;
    }
    isRunning = false;
}

