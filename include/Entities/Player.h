#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Core_System/Const.h"

class Player {
private:
    int x, y;               // Vị trí của nhân vật
    int speed;              // Tốc độ di chuyển
    std::string direction;  // Hướng di chuyển

    SDL_Texture* currentTexture; // Sprite hiện tại của nhân vật
    Animation walkUp, walkDown, walkLeft, walkRight; // Các animation di chuyển

public:
    Player(Graphic& graphic);
    ~Player();

    void init(Graphic& graphic); // Khởi tạo nhân vật
    void handleInput(const SDL_Event& event); // Xử lý input từ bàn phím
    void update(); // Cập nhật trạng thái nhân vật
    void render(Graphic& graphic); // Vẽ nhân vật

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif