#include <iostream>
#include "Graphics_Rendering/Animation.h"

// Constructor with frame delay (default 100ms)
Animation::Animation(Graphic& graphic, Uint32 delay) : graphic(graphic), currentFrame(0), frameDelay(delay), lastUpdate(0) {}

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

void Animation::show(Graphic& graphic, int x, int y, int maxWidth, int maxHeight) {
    if (frames.empty()) {
        std::cerr << "ERROR: No frames to show in animation!" << std::endl;
        return;
    }
    graphic.renderTextureKeepRatio(frames[currentFrame], x, y, maxWidth, maxHeight);
}

void Animation::showBackground(SDL_Texture* texture, int x, int y) {
    if (!texture) {
        std::cerr << "ERROR: No background texture to show!" << std::endl;
        return;
    }
    graphic.renderBackground(texture, x, y);
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
SDL_Texture* Animation::getLastCostume() {
    if (frames.empty()) return nullptr;
    return frames.back();
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

// Resize image
void Animation::setSize(int scale) {
    if (frames.empty()) {
        std::cerr << "ERROR: No frames to set size!" << std::endl;
        return;
    }

    float factor = scale / 100.0f;
    m_scale = scale;

    for (SDL_Texture*& frame : frames) {
        int origW, origH;
        if (SDL_QueryTexture(frame, nullptr, nullptr, &origW, &origH) != 0) {
            std::cerr << "ERROR: Cannot query texture: " << SDL_GetError() << std::endl;
            continue;
        }

        int newW = static_cast<int>(origW * factor);
        int newH = static_cast<int>(origH * factor);

        m_maxWidth = std::max(m_maxWidth, newW);
        m_maxHeight = std::max(m_maxHeight, newH);
    }
}