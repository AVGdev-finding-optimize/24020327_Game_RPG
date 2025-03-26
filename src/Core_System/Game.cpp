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

// Initialize the game
bool Game::initSDL(const char* title, int x, int y, int width, int height, bool fullscreen) {
    std::cout << "Initializing SDL... (message from game)\n";

    if (!graphic.initSDL(width, height, title)) {
        std::cerr << "Error initializing SDL (message from game)" << std::endl;
        return false;
    }

    if (!graphic.getRenderer()) {
        std::cerr << "ERROR: Renderer is NULL after graphic.initSDL()! (message from game)\n";
        return false;
    }

    std::cout << "SDL Initialized successfully! (message from game)\n";

    // Load background
    if (!gameMap.loadBackground(graphic, BACKGROUND_PATH)) {
        std::cerr << "ERROR: Failed to load background (message from game)" << std::endl;
        return false;
    }
    gameMap.loadBackground(graphic, BACKGROUND_PATH);
    gameMap.switchBackground(0);
    std::cout << "Background loaded! (message from game)\n";
    
    // Initialize the player
    if (!graphic.getRenderer()) {
        std::cerr << "ERROR: Renderer is NULL before loading player! (message from game)\n";
        return false;
    }
    player.startAsClone(graphic);
    std::cout << "Player initialized! (message from game)\n";

    // Load all tiles
    loadAllTiles(graphic);
    std::cout << "Tiles loaded! (message from game)\n";
    gameMap.setMapLayoutFromFile(VILLAGE_MAP_PATH); // Load map layout from file
    std::cout << "Map layout loaded! (message from game)\n";
    
    camX = 0;
    camY = 0;

    isRunning = true;
    return true;
}

// Load all tiles from file
void Game::loadAllTiles(Graphic& graphic) { 
    std::ifstream file("D:/CODE/RPG_GAME/assets/tiles/paths.txt"); 

    if (!file.is_open()) { 
        std::cerr << "Can't open file  paths.txt! (message from game)\n"; 
        return; 
    } 

    std::vector<std::string> tilePaths; 
    std::string line; 

    std::cerr << "Loading tiles... (message from game)\n"; 

    while (std::getline(file, line)) { 
        if (!line.empty()) {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            tilePaths.push_back(line);
        }
    }    

    file.close(); 

    // Kiểm tra có load được tiles không
    if (tilePaths.empty()) { 
        std::cerr << "File paths.txt empty or invalid! (message from game)\n"; 
        return; 
    } 

    gameMap.loadTileset(graphic, tilePaths); 

    std::cerr << "🎉 Tiles loaded! Total of tiles: " << tilePaths.size() << " (message from game)" << std::endl; 
}

// Main game loop (Scratch: "forever loop")
void Game::foreverLoop() {
    std::cout << "Game is running... (message from game)\n";
    
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
            std::cerr << "[WARNING] Player texture is NULL! (message from game)\n";
            wasNull = true;
        }
    } else {
        wasNull = false; // Reset flag when texture is valid again
    }
}

// Render game objects (Scratch: "show")
void Game::show() {
    graphic.prepareScene();
    gameMap.show(graphic, -128 - camX % 64, -128 - camY % 64);
    player.show(graphic, player.getX() - camX, player.getY() - camY);
    /* gameMap.showTiles(graphic, 0 - camX, 0 - camY); */
    std::cout << "Calling showTiles - ";
    gameMap.showTiles(graphic, camX, camY);
    std::cout << "Finished (message from game)" << std::endl;

    graphic.presentScene();
}

// Cleanup resources (Scratch: "stop all")
void Game::stopAll() {
    std::cout << "Cleaning up game... (message from game)\n";
}