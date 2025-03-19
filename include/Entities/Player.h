#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <map>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Core_System/Const.h"

class Player {
private:
    double x, y;               // Vị trí của nhân vật
    double joyX, joyY, joyDist;// Hướng di chuyển của nhân vật
    int speed;              // Tốc độ di chuyển
    int direction;  // Hướng di chuyển của nhân vật
    std::map<int, SDL_Texture*> textures; // Danh sách các texture của nhân vật

    SDL_Texture* currentTexture; // Sprite hiện tại của nhân vật
    Animation walkUp, walkDown, walkLeft, walkRight; // Các animation di chuyển

public:
    Player(Graphic& graphic);
    ~Player();

    void init(Graphic& graphic); // Khởi tạo nhân vật
    void handleInputState(const Uint8* keystates); // Xử lý input từ bàn phím
    void tryMove(double dx, double dy); // Thử di chuyển nhân vật
    void updateMovement(); // Cập nhật vị trí nhân vật
    void update(); // Cập nhật trạng thái nhân vật
    void render(Graphic& graphic); // Vẽ nhân vật

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif