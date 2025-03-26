#include "Entities/Player.h"
#include "Core_System/Game.h"

// Constructor
Player::Player(Graphic& graphic): walkUp(graphic, 100), walkDown(graphic, 100), walkLeft(graphic, 100), walkRight(graphic, 100) {
    x = WINDOW_WIDTH / 2 - 10;
    y = WINDOW_HEIGHT / 2 - 16;
    speed = PLAYER_SPEED;
    joyX = 0;
    joyY = 0;
    direction = 180;
    currentCostume = nullptr;
    lastFrameTime = 0;

    startAsClone(graphic);
}

// Destructor
Player::~Player() {
    if (currentCostume) {
        SDL_DestroyTexture(currentCostume);
        currentCostume = nullptr;
        std::cout << "Player costume destroyed! (message from player)\n";
    }
}

// Initialize player textures (equivalent to Scratch's "start as a clone")
void Player::startAsClone(Graphic& graphic) {
    if (!graphic.getRenderer()) {
        std::cerr << "ERROR: Renderer is NULL! Cannot load player textures. (message from player)" << std::endl;
        return;
    }
    std::cout << "Loading player costumes... (message from player)\n"; 
    
    // Set default idle sprites
    walkUp.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/idle0.png"));
    walkDown.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/idle180.png"));
    walkLeft.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/idle-90.png"));
    walkRight.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/idle90.png"));

    // Set default costume to first frame of walkDown
    currentCostume = walkDown.getCurrentCostume();
    direction = 180; 

    // Load walking animation frames
    for (int i = 1; i <= 5; i++) {
        walkUp.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/walk0." + std::to_string(i) + ".png"));
        walkDown.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/walk180." + std::to_string(i) + ".png"));
        walkLeft.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/walk-90." + std::to_string(i) + ".png"));
        walkRight.addCostume(graphic.loadTexture("D:/CODE/RPG_GAME/assets/player/walk90." + std::to_string(i) + ".png"));
    }
    
}

SDL_Texture* Player::getCurrentCostume() const {
    return currentCostume;
}

// Handle keyboard input
void Player::handleInputState(const Uint8* keystates) {
    joyX = (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) - 
           (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]);
    joyY = (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) - 
           (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]);
    joyDist = sqrt(joyX * joyX + joyY * joyY);
    
    bool noKeyPressed = (joyX == 0 && joyY == 0);
    if (noKeyPressed) {
        if (direction == 0) {
            currentCostume = walkUp.getFirstCostume();
            } else if (direction == 180) {
                currentCostume = walkDown.getFirstCostume();
            } else if (direction == -90) {
                currentCostume = walkLeft.getFirstCostume();
            } else if (direction == 90) {
                currentCostume = walkRight.getFirstCostume();
        }
    }
}

void Player::moveSteps() {
    if ( joyDist > 0 ) {
        updateMovement();
    }
}

// Update movement logic
void Player::updateMovement() {
    if (joyDist > 1) {
        joyDist = sqrt(2); // Normalize diagonal movement speed
    }
    joyX /= joyDist;
    joyY /= joyDist;
    tryMove(joyX * speed, joyY * speed);
    
    // Change costume based on direction
    if (joyX < 0) {
        direction = -90;
        currentCostume = walkLeft.getCurrentCostume();
    } else if (joyX > 0) {
        direction = 90;
        currentCostume = walkRight.getCurrentCostume();
    } else if (joyY < 0) {
        direction = 0;
        currentCostume = walkUp.getCurrentCostume();
    } else if (joyY > 0) {
        direction = 180;
        currentCostume = walkDown.getCurrentCostume();
    }

    // Animate movement
    Uint32 currentTime = SDL_GetTicks();
    if (joyDist > 0) {
        if (currentTime - lastFrameTime >= 100) { // Change frame every 0.3s
            lastFrameTime = currentTime;

            // Switch animation frames
            if (direction == 0) {
                walkUp.nextCostume();
                currentCostume = walkUp.getCurrentCostume();
            } else if (direction == 180) {
                walkDown.nextCostume();
                currentCostume = walkDown.getCurrentCostume();
            } else if (direction == -90) {
                walkLeft.nextCostume();
                currentCostume = walkLeft.getCurrentCostume();
            } else if (direction == 90) {
                walkRight.nextCostume();
                currentCostume = walkRight.getCurrentCostume();
            }
        }
    }
}

// Try to move
void Player::tryMove(double dx, double dy) {
    x += dx;
    y += dy;
}

// Update player state
void Player::update() {}

// Show player on screen (equivalent to Scratch's "show")
void Player::show(Graphic& graphic, int camX, int camY) {
    if (!getCurrentCostume()) {
        std::cerr << "WARNING: currentCostume is NULL! (message from player)\n";
        return;
    }

    // Lấy kích thước thực tế của sprite
    int textureW, textureH;
    if (SDL_QueryTexture(getCurrentCostume(), nullptr, nullptr, &textureW, &textureH) != 0) {
        std::cerr << "ERROR: Cannot query texture (message from player): " << SDL_GetError() << std::endl;
        return;
    }

    int footY = (WINDOW_HEIGHT / 2);  
    int screenX = WINDOW_WIDTH / 2;
    int screenY = footY - textureH * UPSCALE; 

    graphic.renderTextureKeepRatio(getCurrentCostume(), screenX, screenY, UPSCALE);
}
