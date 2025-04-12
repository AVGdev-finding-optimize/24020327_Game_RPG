#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Graphics_Rendering/Textengine.h"
#include "Sounds_Effects/Sound.h"
#include "Entities/Player.h"
#include "Core_System/Const.h"
#include "Core_System/Colision.h"
#include "Map/Map.h"

class Game {
private:
    bool isRunning;
    bool isMouseDown = 0;
    Graphic graphic;
    SDL_Texture* currentCostume;
    Player player;
    Map gameMap;
    Sound sound;
    TextEngine* textEngine;
    SDL_Texture* logo;

public:
    Game();
    ~Game();

    void intro();

    int camX, camY;
    int getGameWidth() const { return gameMap.getMapHeight(); }
    int getGameHeight() const { return gameMap.getMapWidth(); }
    int getGameTileSize() const { return gameMap.getTileSize(); }
    
    void loadAllTiles(Graphic& graphic);

    void foreverLoop();
    bool initSDL(const char* title, int x, int y, int width, int height, bool fullscreen); 
    void whenKeyPressed();  
    void handleMouseEvents(SDL_Event& event); 
    void handleKeyboardEvents(SDL_Event& event); 

    void updateGame();  
    void updateCamera(int playerX, int playerY); 
    void show();  
    void stopAll();  

    bool running() { return isRunning; }
    SDL_Texture* getCurrentCostume() const { return currentCostume; } 
    SDL_Renderer* getRenderer() { return graphic.getRenderer(); } 
};

#endif