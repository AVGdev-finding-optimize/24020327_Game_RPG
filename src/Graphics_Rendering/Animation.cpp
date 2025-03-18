#include "Graphics_Rendering/Animation.h"

// Constructor
Animation::Animation() {
    frameCount = 0;
    currentFrame = 0;
    frameDelay = 10; // Mặc định mỗi frame tồn tại 10 lần update
    frameTimer = 0;
}

// Destructor
Animation::~Animation() {
    for (SDL_Texture* frame : frames) {
        SDL_DestroyTexture(frame);
    }
    frames.clear();
}

// Thêm frame vào animation
void Animation::addFrame(SDL_Texture* texture) {
    frames.push_back(texture);
    frameCount++;
}

// Cập nhật animation (tăng frame dựa trên frameDelay)
void Animation::update() {
    if (frameCount > 1) {
        frameTimer++;
        if (frameTimer >= frameDelay) {
            frameTimer = 0;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    }
}

// Lấy frame hiện tại
SDL_Texture* Animation::getCurrentFrame() {
    if (frameCount > 0) {
        return frames[currentFrame];
    }
    return nullptr;
}

// Reset animation về frame đầu tiên
void Animation::reset() {
    currentFrame = 0;
    frameTimer = 0;
}
