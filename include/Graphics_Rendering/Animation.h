#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL2/SDL.h>

class Animation {
private:
    std::vector<SDL_Texture*> frames; // Danh sách các frame ảnh
    int frameCount;  // Số frame ảnh
    int currentFrame; // Frame hiện tại
    int frameDelay;   // Độ trễ giữa các frame
    int frameTimer;   // Bộ đếm thời gian frame

public:
    Animation();
    ~Animation();

    void addFrame(SDL_Texture* texture);
    void update();
    SDL_Texture* getCurrentFrame();
    void reset();
};

#endif