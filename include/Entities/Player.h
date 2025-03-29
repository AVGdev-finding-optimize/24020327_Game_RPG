#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Graphics_Rendering/Textengine.h"
#include "Core_System/Const.h"

class Player {
private:
    double x, y;               // Player position
    double joyX, joyY, joyDist;// Movement direction
    int screenX, screenY;
    int speed;                 // Movement speed
    int direction;             // Movement direction
    SDL_Texture* currentCostume; // Current costume
    Animation walkUp, walkDown, walkLeft, walkRight; // Movement animations
    Uint32 lastFrameTime;     // Last frame time
    int mapWidth, mapHeight, tileSize; // Map dimensions
    int oldSpriteHeight = 0;
    int interpolatedHeight = 0;

public:
    Player(Graphic& graphic);
    ~Player();

    inline void setX(int newX) { x += newX; }
    inline void setY(int newY) { y += newY; }

    void startAsClone(Graphic &graphic); // Initialize player (equivalent to Scratch's "start as a clone")
    void handleInputState(const Uint8* keystates); // Process input
    void moveSteps(int camX, int camY, int mapEditorActive); // Move according to direction (equivalent to "move steps")
    void tryMove(double dx, double dy); // Try to move
    void updateMovement(int camX, int camY, int mapEditorActive); // Update position
    void update(); // Update state (animations)
    void dataCollect(int gameMapHeight, int gameMapWidth, int tile_Size); // Collect data from game
    void show(Graphic& graphic); // Render player (equivalent to "show")
    SDL_Texture* getCurrentCostume() const; // Get current costume

    void setScreenX(int sx) { screenX = sx; }
    void setScreenY(int sy) { screenY = sy; }
    double getX() const { return x; }
    double getY() const { return y; }

};

#endif