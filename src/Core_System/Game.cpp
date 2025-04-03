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
    
    // Render textengine
    textEngine = new TextEngine(graphic.getRenderer());
    textEngine->loadFont("D:/CODE/RPG_GAME/assets/font/#9Slide04 Rokkitt Bold_1.ttf", 24);

    camX = 0;
    camY = 0;

    isRunning = true;
    return true;
}

// Load all tiles from file
void Game::loadAllTiles(Graphic& graphic) { 
    std::ifstream file("D:/CODE/RPG_GAME/assets/tiles/layerpaths.txt"); 

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

    if (tilePaths.empty()) { 
        std::cerr << "File paths.txt empty or invalid! (message from game)\n"; 
        return; 
    } 

    gameMap.loadTileset(graphic, tilePaths); 

    std::cerr << "🎉 Tiles loaded! Total of tiles: " << tilePaths.size() << " (message from game)" << std::endl; 
}

// Main game loop
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

//Handle
void Game::whenKeyPressed() {
    SDL_Event event;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    static bool tPressed = false; // Trạng thái phím T

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            isMouseDown = true;
            gameMap.handleMousePalette(event.button.button);
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            isMouseDown = false; 
        }
        if (event.type == SDL_MOUSEMOTION) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            gameMap.updateMousePosition(mouseX, mouseY, camX, camY);

            if (isMouseDown) { 
                gameMap.handleMousePalette(SDL_BUTTON_LEFT); 
            }
        }
        if (event.type == SDL_MOUSEWHEEL) {
            gameMap.handleMouseWheelPalette(event.wheel.y);
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_m) { 
                gameMap.saveMapToFile(VILLAGE_MAP_PATH);
            }
            if (event.key.keysym.sym == SDLK_e) {
                gameMap.eraseTile = !gameMap.eraseTile;
            }
            if (event.key.keysym.sym == SDLK_t && !tPressed) { 
                tPressed = true; 
                gameMap.paletteOpen = !gameMap.paletteOpen;
                updateGame();
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_t) {
                tPressed = false;
            }
        }
    }

    player.handleInputState(keystates);
}

// Camera
void Game::updateCamera(int playerX, int playerY) {
    int camXOffset = gameMap.paletteOpen ? PALETTE_WIDTH : 0;
    if (gameMap.isMapEditorActive()) {
        camXOffset = gameMap.paletteOpen ? PALETTE_WIDTH : 0;
    } else {
        camXOffset = 0;
    }
    camX = playerX - (WINDOW_WIDTH / 2) + camXOffset;
    camY = playerY - (WINDOW_HEIGHT / 2);

    // Giữ camera theo khoảng cách với player
    if (playerX < camX + WINDOW_WIDTH / 2) {
        camX = playerX - (WINDOW_WIDTH / 2) - camXOffset;
    }
    if (playerX > camX + WINDOW_WIDTH / 2) {
        camX = playerX - (WINDOW_WIDTH / 2) - camXOffset;
    }
    if (playerY < camY + WINDOW_HEIGHT / 2) {
        camY = playerY - (WINDOW_HEIGHT / 2);
    }
    if (playerY > camY + WINDOW_HEIGHT / 2) {
        camY = playerY - (WINDOW_HEIGHT / 2);
    }

    // Giới hạn camera trong bản đồ
    if (camX < 0) camX = 0;
    if (camY < 0) camY = 0;
    if (camX + WINDOW_WIDTH > gameMap.getMapWidth() * gameMap.getTileSize() * UPSCALE + camXOffset) 
        camX = gameMap.getMapWidth() * gameMap.getTileSize() * UPSCALE - WINDOW_WIDTH + camXOffset;
    if (camY + WINDOW_HEIGHT > gameMap.getMapHeight() * gameMap.getTileSize() * UPSCALE) 
        camY = gameMap.getMapHeight() * gameMap.getTileSize() * UPSCALE - WINDOW_HEIGHT;
}

// Update game logic 
void Game::updateGame() {
    if (!isRunning) return;  // Exit early if the game is not running
    updateCamera(player.getX(), player.getY());
    player.update();       // Update player logic
    player.moveSteps(camX, camY);    // Process player movement

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

// Render game objects
void Game::show() {
    graphic.prepareScene();
    gameMap.show(graphic, -128 - camX % 64, -128 - camY % 64);
    player.dataCollect(gameMap.getMapHeight(), gameMap.getMapWidth(), gameMap.getTileSize());
    gameMap.showTiles(graphic, camX, camY);
    player.show(graphic);
    if (gameMap.isMapEditorActive()) {
        gameMap.highlightCursor(camX, camY);
        if (gameMap.isPaletteOpen()) {
            gameMap.showPalette();
            gameMap.displayPaintBrushTileID(textEngine);
        }
    }
    graphic.presentScene();
}

void Game::stopAll() {
    std::cout << "Cleaning up game... (message from game)\n";
}