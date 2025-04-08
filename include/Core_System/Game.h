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

    // Camera and scrolling system
    int camX, camY; // Camera position
    int getGameWidth() const { return gameMap.getMapHeight(); }
    int getGameHeight() const { return gameMap.getMapWidth(); }
    int getGameTileSize() const { return gameMap.getTileSize(); }
    
    // Tile System & Level Map
    void loadAllTiles(Graphic& graphic); // Load all tiles from file

    // Game loop
    void foreverLoop(); // Scratch-style "forever" loop (game loop)
    bool initSDL(const char* title, int x, int y, int width, int height, bool fullscreen); // Init game
    void whenKeyPressed();  // Handle events
    void handleMouseEvents(SDL_Event& event); // Handle mouse events
    void handleKeyboardEvents(SDL_Event& event); // Handle keyboard events

    // Update && show
    void updateGame();  // Update game state
    void updateCamera(int playerX, int playerY);  // Update camera position
    void show();  // Render graphics
    void stopAll();  // Clean up resources

    bool running() { return isRunning; }
    SDL_Texture* getCurrentCostume() const { return currentCostume; } // Get current background
    SDL_Renderer* getRenderer() { return graphic.getRenderer(); } // Get renderer
};

#endif