#include "Entities/Player.h"
#include <iostream>
#include <cmath>

// Constructor: Khởi tạo vị trí, tốc độ và hướng mặc định của nhân vật
Player::Player(Graphic& graphic) {
    x = WINDOW_WIDTH / 2;   // Đặt nhân vật vào giữa màn hình
    y = WINDOW_HEIGHT / 2;
    speed = PLAYER_SPEED;
    joyX = 0;
    joyY = 0;
    direction = 180;
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
    //Debug
    std::cout << "Loading textures for player..." << std::endl;
    
    std::map<int, std::string> texturePaths = {
        {0, "assets/player/idle0.png"},
        {90, "assets/player/idle90.png"},
        {-90, "assets/player/idle-90.png"},
        {180, "assets/player/idle180.png"}
    };

    for (const auto& pair : texturePaths) {
        std::cout << "Loading texture: " << pair.second << " for direction " << pair.first << std::endl;
        textures[pair.first] = graphic.loadTexture(pair.second.c_str());

        if (textures[pair.first] == nullptr) {
            std::cout << "ERROR: Failed to load texture for direction " << pair.first << std::endl;
        }
    }

    //Tải lên các animation di chuyển
    textures[0] = graphic.loadTexture("assets/player/idle0.png");
    textures[45] = graphic.loadTexture("assets/player/idle0.png");
    textures[90] = graphic.loadTexture("assets/player/idle90.png");
    textures[135] = graphic.loadTexture("assets/player/idle180.png");
    textures[180] = graphic.loadTexture("assets/player/idle180.png");
    textures[-135] = graphic.loadTexture("assets/player/idle180.png");
    textures[-90] = graphic.loadTexture("assets/player/idle-90.png");
    textures[-45] = graphic.loadTexture("assets/player/idle0.png");

    // Đặt sprite ban đầu
    direction = 180;
    currentTexture = textures[direction];
}

// Xử lý input từ bàn phím
void Player::handleInputState(const Uint8* keystates) {
    int newDirection = direction;
    bool moving = false;

    if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) {
        newDirection = 0; moving = true;
    }
    if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) {
        newDirection = 180; moving = true;
    }
    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
        newDirection = -90; moving = true;
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
        newDirection = 90; moving = true;
    }
    if ((keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) &&
        (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W])) {
        newDirection = -45;
    }
    if ((keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) &&
        (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W])) {
        newDirection = 45;
    }
    if ((keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) &&
        (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])) {
        newDirection = -135;
    }
    if ((keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) &&
        (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])) {
        newDirection = 135;
    }

    if (textures.find(direction) != textures.end()) { 
        currentTexture = textures[direction];
    }

    if (moving) {
        direction = newDirection;
        currentTexture = textures[direction];
    }

    if (!moving) {
        joyX = 0; joyY = 0;
    }
}

void Player::updateMovement() {
    joyDist = sqrt(joyX * joyX + joyY * joyY);
    
    if (joyDist > 0) {
        double normX = joyX / joyDist;
        double normY = joyY / joyDist;
        tryMove(normX * speed, normY * speed);
    }
}

void Player::tryMove(double dx, double dy) {
    x += dx;
    y += dy;
}

// Cập nhật trạng thái nhân vật (hoạt ảnh)
void Player::update() {
    //Debug
    std::cout << "Player update - Current Texture: " << (currentTexture ? "OK" : "NULL") << std::endl;

    if (direction == 0) {
        currentTexture = walkUp.getCurrentFrame();
    } else if (direction == 180) {
        currentTexture = walkDown.getCurrentFrame();
    } else if (direction == -90) {
        currentTexture = walkLeft.getCurrentFrame();
    } else if (direction == 90) {
        currentTexture = walkRight.getCurrentFrame();
    }
}

// Vẽ nhân vật lên màn hình
void Player::render(Graphic& graphic) {
    graphic.renderTexture(currentTexture, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}