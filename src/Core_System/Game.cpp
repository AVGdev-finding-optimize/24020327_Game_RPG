#include "Core_System/Game.h"
#define SDL_MAIN_HANDLED


Uint32 frameStart;
int frameTime;

// Constructor
Game::Game() : player(graphic), gameMap(graphic), camX(0), camY(0) {
    isRunning = false;
    currentCostume = nullptr;
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

    SDL_Texture* bgTexture = graphic.loadTexture(BACKGROUND_PATH);
    if (!bgTexture) {
        std::cerr << "Error loading background" << std::endl;
        return false;
    }
    
    // Load background and tiles
    gameMap.loadBackground(graphic, BACKGROUND_PATH);
    loadAllTiles();
    gameMap.switchBackground(0);

    std::cout << "Background loaded!\n";
    
    // Initialize the player
    player.startAsClone(graphic);
    std::cout << "Player initialized!\n";

    camX = 0;
    camY = 0;

    isRunning = true;
    return true;
}

// Load all tiles from file
void Game::loadAllTiles() {
    std::ifstream file("assets/tiles/TITLES.txt");
    std::vector<std::string> tilePaths;
    std::string line;

    while (std::getline(file, line)) {
        tilePaths.push_back(line);
    }

    file.close();
    gameMap.loadTileset(graphic, tilePaths);
}

// Main game loop (Scratch: "forever loop")
void Game::foreverLoop() {
    std::cout << "Game is running...\n";
    while (isRunning) {
        frameStart = SDL_GetTicks();

        updateCamera(player.getX(), player.getY()); // Update camera position
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

// Camera
void Game::updateCamera(int playerX, int playerY) {
    camX = player.getX() - (WINDOW_WIDTH / 2);
    camY = player.getY() - (WINDOW_HEIGHT / 2);

    if (playerX < camX + WINDOW_WIDTH / 2 - CAMERA_MARGIN_X) {
        camX = playerX - (WINDOW_WIDTH / 2 - CAMERA_MARGIN_X);
    }
    if (playerX > camX + WINDOW_WIDTH / 2 + CAMERA_MARGIN_X) {
        camX = playerX - (WINDOW_WIDTH / 2 + CAMERA_MARGIN_X);
    }
    if (playerY < camY + WINDOW_HEIGHT / 2 - CAMERA_MARGIN_Y) {
        camY = playerY - (WINDOW_HEIGHT / 2 - CAMERA_MARGIN_Y);
    }
    if (playerY > camY + WINDOW_HEIGHT / 2 + CAMERA_MARGIN_Y) {
        camX = playerY - (WINDOW_HEIGHT / 2 + CAMERA_MARGIN_Y);
    }
}

// Update game logic 
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
    gameMap.show(graphic, - camX, - camY);
    player.show(graphic, player.getX() - camX, player.getY() - camY);
    graphic.presentScene();
}

// Cleanup resources (Scratch: "stop all")
void Game::stopAll() {
    std::cout << "Cleaning up game...\n";
}