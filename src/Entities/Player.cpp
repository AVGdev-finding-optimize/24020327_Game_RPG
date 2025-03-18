#include "Entities/Player.h"
#include <iostream>
#include <cmath>

// Constructor: Khởi tạo vị trí, tốc độ và hướng mặc định của nhân vật
Player::Player(Graphic& graphic) {
    x = WINDOW_WIDTH / 2;   // Đặt nhân vật vào giữa màn hình
    y = WINDOW_HEIGHT / 2;
    speed = PLAYER_SPEED;
    direction = "down";
    currentTexture = nullptr;

    init(graphic); // Khởi tạo hoạt ảnh của nhân vật
}

// Destructor: Giải phóng bộ nhớ khi Player bị hủy
Player::~Player() {
    if (currentTexture) {
        SDL_DestroyTexture(currentTexture);
        currentTexture = nullptr;
        std::cout << "Player texture destroyed!\n";
    }
}

// Khởi tạo hoạt ảnh của nhân vật
void Player::init(Graphic& graphic) {
    for (int i = 1; i <= 5; ++i) { // Hoạt ảnh có 5 frame
        std::string pathUp = "assets/player/walk0." + std::to_string(i) + ".png";
        std::string pathRight = "assets/player/walk90." + std::to_string(i) + ".png";
        std::string pathLeft = "assets/player/walk-90." + std::to_string(i) + ".png";
        std::string pathDown = "assets/player/walk180." + std::to_string(i) + ".png";

        walkUp.addFrame(graphic.loadTexture(pathUp.data()));
        walkRight.addFrame(graphic.loadTexture(pathRight.data()));
        walkLeft.addFrame(graphic.loadTexture(pathLeft.data()));
        walkDown.addFrame(graphic.loadTexture(pathDown.data()));
    }
    currentTexture = walkDown.getCurrentFrame(); // Mặc định hướng xuống
}

// Xử lý input từ bàn phím
void Player::handleInput(const SDL_Event& event) {
    int joyX = 0;
    int joyY = 0;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                joyY = -1;
                direction = "up";
                currentTexture = walkUp.getCurrentFrame();
                break;
            case SDLK_DOWN:
            case SDLK_s:
                joyY = 1;
                direction = "down";
                currentTexture = walkDown.getCurrentFrame();
                break;
            case SDLK_LEFT:
            case SDLK_a:
                joyX = -1;
                direction = "left";
                currentTexture = walkLeft.getCurrentFrame();
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                joyX = 1;
                direction = "right";
                currentTexture = walkRight.getCurrentFrame();
                break;
        }
    }

    float joyDist = std::sqrt(joyX * joyX + joyY * joyY);

    if (joyDist > 0) {
        joyX /= joyDist;
        joyY /= joyDist;

        x += joyX * speed;
        y += joyY * speed;
    }
}

// Cập nhật trạng thái nhân vật (hoạt ảnh)
void Player::update() {
    if (direction == "up") {
        currentTexture = walkUp.getCurrentFrame();
    } else if (direction == "down") {
        currentTexture = walkDown.getCurrentFrame();
    } else if (direction == "left") {
        currentTexture = walkLeft.getCurrentFrame();
    } else if (direction == "right") {
        currentTexture = walkRight.getCurrentFrame();
    }
}

// Vẽ nhân vật lên màn hình
void Player::render(Graphic& graphic) {
    graphic.renderTexture(currentTexture, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}