#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL2/SDL.h>
#include "Graphic.h"

class Animation {
private:
    std::vector<SDL_Texture*> frames;
    Uint32 currentFrame;
    Uint32 frameDelay;
    Uint32 lastUpdate;

public:
    Animation(Uint32 delay = 100);
    ~Animation();

    void addCostume(SDL_Texture* texture);  // Add a new costume
    void nextCostume(); // Change to the next frame
    void switchCostume(int costumeIndex);   // Switch to a different costume
    void show(Graphic& graphic, int x, int y, int w, int h); // Render the current frame

    SDL_Texture* getCurrentCostume(); // Get the current frame
    SDL_Texture* getFirstCostume(); // Get the first frame
    SDL_Texture* getLastCostume(int index); // Get a specific frame

    void update(); // Update the frame based on time
    void clear(); // Free memory

    void setSize(int scale); // Resize (not implemented yet)
};

#endif