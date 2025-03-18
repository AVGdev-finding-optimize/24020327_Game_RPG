#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL2/SDL.h>

class Animation {
private:
    std::vector<SDL_Texture*> frames; // Danh sách các frame của animation
    int currentFrame; // Frame hiện tại
    Uint32 frameDelay; // Thời gian giữa các frame
    Uint32 lastUpdate; // Thời gian cập nhật cuối cùng

public:
    Animation(Uint32 delay = 100); // Constructor với thời gian mặc định giữa các frame
    ~Animation();

    void addFrame(SDL_Texture* texture); // Thêm frame mới vào animation
    SDL_Texture* getCurrentFrame(); // Lấy frame hiện tại của animation
    void update(); // Cập nhật frame animation theo thời gian
    void clean(); // Dọn dẹp bộ nhớ
};

#endif