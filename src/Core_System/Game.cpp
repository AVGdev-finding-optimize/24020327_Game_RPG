#include "Core_System/Game.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

Uint32 frameStart;
int frameTime;

// Constructor
Game::Game() : player(graphic) {
    isRunning = false;
    currentCostume = nullptr;  // Initialize currentCostume
}

// Destructor
Game::~Game() {
    stopAll();
}

// Initialize the game (Scratch: "when Green Flag clicked")
bool Game::initSDL(const char* title, int x, int y, int width, int height, bool fullscreen) {
    std::cout << "Initializing SDL...\n";

    if (!graphic.initSDL(width, height, title)) {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    std::cout << "SDL Initialized!\n";

    // Load background as an animation object
    SDL_Texture* bgTexture = graphic.loadTexture(BACKGROUND_PATH);
    if (!bgTexture) {
        std::cerr << "Error loading background" << std::endl;
        return false;
    }
    
    background.addCostume(bgTexture);  
    currentCostume = bgTexture;  // Set currentCostume to background texture

    std::cout << "Background loaded!\n";
    
    // Initialize the player
    player.startAsClone(graphic);
    std::cout << "Player initialized!\n";
    
    isRunning = true;
    return true;
}

// Main game loop (Scratch: "forever loop")
void Game::foreverLoop() {
    std::cout << "Game is running...\n";
    while (isRunning) {
        frameStart = SDL_GetTicks();

        whenKeyPressed(); // Handle inputs
        updateGame();      // Update game logic
        show();           // Render graphics

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}

// Handle events (Scratch: "when key pressed")
void Game::whenKeyPressed() {
    SDL_Event event;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
    
    player.handleInputState(keystates);
}

// Update game logic (Scratch: "when I receive")
void Game::updateGame() {
    if (!isRunning) return;  // Exit early if the game is not running

    player.update();       // Update player logic
    player.moveSteps();    // Process player movement

    // Optimized Debugging: Only log once when texture becomes NULL
    static bool wasNull = false; // Track previous texture state
    if (!player.getCurrentCostume()) {  // Use getter function
        if (!wasNull) {  // Log only when texture first turns NULL
            std::cerr << "[WARNING] Player texture is NULL!\n";
            wasNull = true;
        }
    } else {
        wasNull = false; // Reset flag when texture is valid again
    }
}


// Render game objects (Scratch: "show")
void Game::show() {
    graphic.prepareScene();
    background.show(graphic, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // Render background using animation
    player.show(graphic);
    graphic.presentScene();
}

// Cleanup resources (Scratch: "stop all")
void Game::stopAll() {
    std::cout << "Cleaning up game...\n";
}