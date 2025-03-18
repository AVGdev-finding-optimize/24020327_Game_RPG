#include "Entities/Player.h"
#include <iostream>

Player::Player(Graphic& graphic) {
    x = WINDOW_WIDTH / 2;
    y = WINDOW_HEIGHT / 2;
    speed = PLAYER_SPEED;
    direction = "down";

    // Load hình ảnh mặc định của nhân vật
    currentTexture = graphic.loadTexture(PLAYER_SPRITE_PATH);
    if (currentTexture == nullptr) {
        std::cerr << "Error loading player sprite!\n";
    }
}

Player::~Player() {
    if (currentTexture) {
        SDL_DestroyTexture(currentTexture);
        currentTexture = nullptr;
        std::cout << "Player texture destroyed!\n";
    }
}

void Player::init(Graphic& graphic) {
    // Load sprite đứng yên
    idleDown.addFrame(graphic.loadTexture("assets/player/idle180.png"));
    idleLeft.addFrame(graphic.loadTexture("assets/player/idle-90.png"));
    idleRight.addFrame(graphic.loadTexture("assets/player/idle90.png"));
    idleUp.addFrame(graphic.loadTexture("assets/player/idle0.png"));

    // Load sprite đi bộ
    for (int i = 1; i <= 5; i++) {
        walkUp.addFrame(graphic.loadTexture("assets/player/walk0." + std::to_string(i) + ".png"));
        walkRight.addFrame(graphic.loadTexture("assets/player/walk90." + std::to_string(i) + ".png"));
        walkLeft.addFrame(graphic.loadTexture("assets/player/walk-90." + std::to_string(i) + ".png"));
        walkDown.addFrame(graphic.loadTexture("assets/player/walk180." + std::to_string(i) + ".png"));
    }

    // Set ảnh ban đầu
    currentTexture = idleDown.getCurrentFrame();
}

void Player::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w: direction = "up"; break;
            case SDLK_s: direction = "down"; break;
            case SDLK_a: direction = "left"; break;
            case SDLK_d: direction = "right"; break;
        }
    }
}

void Player::update() {
    if (direction == "up") {
        y -= speed;
        currentTexture = walkUp.getCurrentFrame();
    } else if (direction == "down") {
        y += speed;
        currentTexture = walkDown.getCurrentFrame();
    } else if (direction == "left") {
        x -= speed;
        currentTexture = walkLeft.getCurrentFrame();
    } else if (direction == "right") {
        x += speed;
        currentTexture = walkRight.getCurrentFrame();
    }
}

void Player::render(Graphic& graphic) {
    graphic.renderTexture(currentTexture, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}