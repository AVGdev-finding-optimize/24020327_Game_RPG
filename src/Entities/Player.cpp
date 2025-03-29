#include "Entities/Player.h"
#include "Core_System/Game.h"

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Constructor
Player::Player(Graphic& graphic): walkUp(graphic, 100), walkDown(graphic, 100), walkLeft(graphic, 100), walkRight(graphic, 100) {
    x = WINDOW_WIDTH;
    y = WINDOW_HEIGHT;
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

void Player::moveSteps(int camX, int camY, int paletteOpen) {
    if (joyDist > 0) {
        updateMovement(camX, camY, paletteOpen);
    }
}

// Update movement logic
void Player::updateMovement(int camX, int camY, int paletteOpen) {
    if (joyDist > 1) {
        joyDist = sqrt(2); // Normalize diagonal movement speed
    }
    joyX /= joyDist;
    joyY /= joyDist;

    int textureW, textureH;
    if (SDL_QueryTexture(getCurrentCostume(), nullptr, nullptr, &textureW, &textureH) != 0) {
        textureH = 0; 
    }
    int playerHeight = textureH * UPSCALE;
    int playerWidth = textureW * UPSCALE;

    int camXOffset = paletteOpen ? -340 : 0;
    
    bool camLockedX = (camX <= 32 || camX + WINDOW_WIDTH >= (mapWidth * tileSize * UPSCALE + camXOffset - 32));
    bool camLockedY = (camY <= 32 || camY + WINDOW_HEIGHT >= mapHeight * tileSize * UPSCALE);

    if (!camLockedX) {
        x += joyX * speed;
        screenX = (WINDOW_WIDTH + camXOffset) / 2;
    } else {
        screenX = clamp(screenX + joyX * speed, 0, WINDOW_WIDTH - playerWidth -  camXOffset);
        x += joyX * speed;
    }

    if (!camLockedY) {
        y += joyY * speed;
        screenY = WINDOW_HEIGHT / 2;
    } else {
        screenY = clamp(screenY + joyY * speed, 0, WINDOW_HEIGHT - playerHeight);
        y += joyY * speed;
    }

    // Thay đổi animation theo hướng di chuyển
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

    // Xử lý animation
    Uint32 currentTime = SDL_GetTicks();
    if (joyDist > 0) {
        if (currentTime - lastFrameTime >= 100) { 
            lastFrameTime = currentTime;

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

void Player::dataCollect(int gameMapHeight, int gameMapWidth, int tile_Size) {
    mapWidth = gameMapWidth;
    mapHeight = gameMapHeight;
    tileSize = tile_Size;
}

void Player::show(Graphic& graphic) {
    if (!getCurrentCostume()) return;

    int textureW, textureH;
    if (SDL_QueryTexture(getCurrentCostume(), nullptr, nullptr, &textureW, &textureH) != 0) {
        return;
    }

    int spriteHeight = textureH * UPSCALE;
    int footY = screenY + interpolatedHeight;
    int adjustedScreenY = footY - spriteHeight;

    graphic.renderTextureKeepRatio(getCurrentCostume(), screenX, adjustedScreenY, UPSCALE);

    float smoothingFactor = 0.2f;
    interpolatedHeight = interpolatedHeight * (1.0f - smoothingFactor) + spriteHeight * smoothingFactor;

    oldSpriteHeight = spriteHeight;
}