#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Core_System/Const.h"

class Player {
private:
    double x, y;               // Player position
    double joyX, joyY, joyDist;// Movement direction
    int speed;                 // Movement speed
    int direction;             // Movement direction
    SDL_Texture* currentCostume; // Current costume
    Animation walkUp, walkDown, walkLeft, walkRight; // Movement animations
    Uint32 lastFrameTime;     // Last frame time

public:
    Player(Graphic& graphic);
    ~Player();

    void startAsClone(Graphic &graphic); // Initialize player (equivalent to Scratch's "start as a clone")
    void switchCostume(Graphic &graphic); // Load player sprites (equivalent to Scratch's "switch costume")
    void handleInputState(const Uint8* keystates); // Process input
    void moveSteps(); // Move according to direction (equivalent to "move steps")
    void tryMove(double dx, double dy); // Try to move
    void updateMovement(); // Update position
    void update(); // Update state (animations)
    void show(Graphic& graphic); // Render player (equivalent to "show")
    SDL_Texture* getCurrentCostume() const; // Get current costume

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif