#include "Graphics_Rendering/Animation.h"
#include <SDL2/SDL.h>

// Constructor với thời gian giữa các frame (mặc định 100ms)
Animation::Animation(Uint32 delay) : currentFrame(0), frameDelay(delay), lastUpdate(0) {}

// Destructor - Giải phóng bộ nhớ của các frame
Animation::~Animation() {
    clean();
}

// Thêm một frame mới vào danh sách
void Animation::addFrame(SDL_Texture* texture) {
    if (texture) {
        frames.push_back(texture);
    }
}

// Lấy frame hiện tại của animation
SDL_Texture* Animation::getCurrentFrame() {
    if (frames.empty()) return nullptr;
    return frames[currentFrame];
}

// Cập nhật frame theo thời gian
void Animation::update() {
    Uint32 now = SDL_GetTicks();
    if (now - lastUpdate >= frameDelay) {
        currentFrame = (currentFrame + 1) % frames.size();
        lastUpdate = now;
    }
}

// Dọn dẹp bộ nhớ, giải phóng texture
void Animation::clean() {
    for (SDL_Texture* texture : frames) {
        SDL_DestroyTexture(texture);
    }
    frames.clear();
}