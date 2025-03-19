#include <iostream>
#include "Graphics_Rendering/Animation.h"

// Constructor with frame delay (default 100ms)
Animation::Animation(Uint32 delay) : currentFrame(0), frameDelay(delay), lastUpdate(0) {}

// Destructor - Free memory for frames
Animation::~Animation() {
    clear();
}

// Add a new costume to the list
void Animation::addCostume(SDL_Texture* texture) {
    if (texture) {
        frames.push_back(texture);
    }
}

void Animation::show(Graphic& graphic, int x, int y, int w, int h) {
    if (frames.empty()) {
        std::cerr << "ERROR: No frames to show in animation!" << std::endl;
        return;
    }
    graphic.renderTexture(frames[currentFrame], x, y, w, h);
}

// Switch to a specific costume by index
void Animation::switchCostume(int costumeIndex) {
    if (costumeIndex >= 0 && costumeIndex < static_cast<int>(frames.size())) {
        currentFrame = costumeIndex;
    } else {
        std::cerr << "ERROR: Invalid costume index " << costumeIndex << std::endl;
    }
}

// Change to the next frame (equivalent to "next costume")
void Animation::nextCostume() {
    if (!frames.empty()) {
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

// Get the first frame of the animation (equivalent to "get first costume")
SDL_Texture* Animation::getFirstCostume() {
    if (frames.empty()) return nullptr;
    return frames[0];  // Return the first frame
}

// Get the current frame of the animation (equivalent to "get current costume")
SDL_Texture* Animation::getCurrentCostume() {
    if (frames.empty()) return nullptr;
    return frames[currentFrame];
}

// Get the last frame of the animation (equivalent to "get costume N")
SDL_Texture* Animation::getLastCostume(int index) {
    if (frames.empty()) return nullptr;
    return frames[index];
}

// Update frame based on time
void Animation::update() {
    Uint32 now = SDL_GetTicks();
    if (now - lastUpdate >= frameDelay) {
        nextCostume();
        lastUpdate = now;
    }
}

// Free memory and clear textures
void Animation::clear() {
    for (SDL_Texture* texture : frames) {
        SDL_DestroyTexture(texture);
    }
    frames.clear();
}

// Resize image (not implemented yet)
void Animation::setSize(int scale) {
    // SDL_Texture does not support direct resizing
    // Additional code is needed to implement this
}