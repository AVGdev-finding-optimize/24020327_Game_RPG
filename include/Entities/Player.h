#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <string>
#include "Graphics_Rendering/Animation.h"
#include "Graphics_Rendering/Graphic.h"
#include "Core_System/Const.h"

class Player {
private:
    int x, y;              // Vị trí của nhân vật
    int speed;             // Tốc độ di chuyển
    std::string direction; // Hướng di chuyển
    SDL_Texture* currentTexture; // Ảnh hiện tại
    Animation idleUp, idleDown, idleLeft, idleRight;
    Animation walkUp, walkDown, walkLeft, walkRight;

public:
    Player(Graphic& graphic);
    ~Player();

    void init(Graphic& graphic);
    void handleInput(const SDL_Event& event);
    void update();
    void render(Graphic& graphic);
};

#endif