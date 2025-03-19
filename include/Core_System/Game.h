#ifndef GAME_H
#define GAME_H

#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Entities/Player.h"
#include "Core_System/Const.h"

class Game {
private:
    bool isRunning;
    Graphic graphic;
    Animation background; // Background is now an animation object
    Player player;
    SDL_Texture* currentCostume;

public:
    Game();
    ~Game();
    
    void foreverLoop(); // Scratch-style "forever" loop (game loop)
    bool initSDL(const char* title, int x, int y, int width, int height, bool fullscreen); // Init game
    void whenKeyPressed();  // Handle events
    void updateGame();  // Update game state
    void show();  // Render graphics
    void stopAll();  // Clean up resources

    bool running() { return isRunning; }
    SDL_Texture* getCurrentCostume() const { return currentCostume; } // Get current background
    SDL_Renderer* getRenderer() { return graphic.getRenderer(); } // Get renderer
};

#endif
