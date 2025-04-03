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
    double x, y;               
    double joyX, joyY, joyDist;
    int screenX = WINDOW_WIDTH / 2;
    int screenY = WINDOW_HEIGHT / 2;
    int speed;                 
    int direction;             
    SDL_Texture* currentCostume; 
    Animation walkUp, walkDown, walkLeft, walkRight; 
    Uint32 lastFrameTime;     // Last frame time
    int mapWidth, mapHeight, tileSize; 
    int oldSpriteHeight = 0;
    int interpolatedHeight = 0;

public:
    Player(Graphic& graphic);
    ~Player();

    inline void setX(int newX) { x += newX; }
    inline void setY(int newY) { y += newY; }

    void startAsClone(Graphic &graphic); 
    void handleInputState(const Uint8* keystates); 
    void moveSteps(int camX, int camY); 
    void tryMove(double dx, double dy); 
    void updateMovement(int camX, int camY);
    void update(); 
    void dataCollect(int gameMapHeight, int gameMapWidth, int tile_Size); 
    void show(Graphic& graphic);
    SDL_Texture* getCurrentCostume() const;
    void setScreenX(int sx) { screenX = sx; }
    void setScreenY(int sy) { screenY = sy; }
    double getX() const { return x; }
    double getY() const { return y; }

};

#endif