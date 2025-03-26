#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL2/SDL.h>
#include "Graphic.h"

class Animation {
private:
    std::vector<SDL_Texture*> frames;
    Graphic& graphic;
    Uint32 currentFrame;
    Uint32 frameDelay;
    Uint32 lastUpdate;
    int m_maxWidth = 0;
    int m_maxHeight = 0;
    int m_scale = 1;

public:
    Animation(Graphic& graphic, Uint32 delay = 100);
    ~Animation();

    void addCostume(SDL_Texture* texture);  // Add a new costume
    void nextCostume(); // Change to the next frame
    void previousCostume();
    void switchCostume(int costumeIndex);   // Switch to a different costume
    void show(Graphic& graphic, int x, int y); // Render the current frame
    void showBackground(SDL_Texture* texture, int x, int y); // Render the background

    SDL_Texture* getCurrentCostume(); // Get the current frame
    SDL_Texture* getFirstCostume(); // Get the first frame
    SDL_Texture* getLastCostume(); // Get a specific frame

    void update(); // Update the frame based on time
    void clear(); // Free memory

    void setSize(int scale); // Resize
};

#endif