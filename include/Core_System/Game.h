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
#include "Entities/Player.h"
#include "Core_System/Const.h"
#include "Map/Map.h"

class Game {
private:
    bool isRunning;
    Graphic graphic;
    SDL_Texture* currentCostume;
    Player player;
    Map gameMap;
public:
    Game();
    ~Game();
    
    // Camera and scrolling system
    int camX, camY; // Camera position

    // Infinite scrolling background
    void scrollBackground(int speedX, int speedY);

    // Tile System & Level Map
    
    void loadAllTiles(Graphic& graphic); // Load all tiles from file

    // Game loop
    void foreverLoop(); // Scratch-style "forever" loop (game loop)
    bool initSDL(const char* title, int x, int y, int width, int height, bool fullscreen); // Init game
    void whenKeyPressed();  // Handle events
    void updateGame();  // Update game state
    void updateCamera(int playerX, int playerY);  // Update camera position
    void show();  // Render graphics
    void stopAll();  // Clean up resources

    bool running() { return isRunning; }
    SDL_Texture* getCurrentCostume() const { return currentCostume; } // Get current background
    SDL_Renderer* getRenderer() { return graphic.getRenderer(); } // Get renderer
};

#endif