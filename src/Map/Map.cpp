#include "Map.h"
#include <iostream>

// Constructor
Map::Map(Graphic& graphic) 
    : graphic(graphic), background(graphic, 100), tileSize(32), mapWidth(0), mapHeight(0) {
    tileMap.clear();
    tiles.clear();
}

// Destructor - Free tile textures
Map::~Map() {
    for (auto tile : tiles) {
        SDL_DestroyTexture(tile);
    }
    tiles.clear();
}

// Switch background to a specific costume
void Map::switchBackground(int index) {
    background.switchCostume(index);
}
// Load background as an animation object
bool Map::loadBackground(Graphic& graphic, const std::string& path) {
    SDL_Texture* bgTexture = graphic.loadTexture(path);
    if (bgTexture) {
        background.addCostume(bgTexture);
        return true;  // Thành công
    } else {
        std::cerr << "ERROR: Failed to load background (message from map) " << path << std::endl;
        return false; // Thất bại
    }
}

// Load tileset from file paths
void Map::loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths) {
    for (const auto& path : tilePaths) {
        if (path.empty()) {
            std::cerr << "ERROR: Empty file path! Cannot load texture. (message from map)" << std::endl;
            return;
        }        
        SDL_Texture* tile = graphic.loadTexture(path.c_str());
        if (tile) {
            tiles.push_back(tile);
        } else {
            std::cerr << "ERROR: Failed to load tile (message from map) " << path << std::endl;
        }
    }
    if (tiles.empty()) {
        std::cerr << "ERROR: No tiles loaded! Cannot render map. (message from map)\n";
        return;
    }
    std::cerr << "🎉 Tiles loaded! Totals of tiles  (message from map): " << tiles.size() << std::endl;
}

// Set map layout using a 2D vector
void Map::setMapLayoutFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR: Cannot open map file (message from map) " << filename << std::endl;
        return;
    }

    tileMap.clear();
    
    std::string line;
    int rowIndex = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int tileID;
        while (iss >> tileID) {
            std::cerr << "DEBUG (message from map): Raw tile path (message from map): [" << line << "]" << std::endl;

            if (tileID >= 0 && tileID < static_cast<int>(tiles.size())) { 
                row.push_back(tileID);
            } else {
                std::cerr << "WARNING (message from map): Tile ID " << tileID << " is out of range! Using the first tile (ID 0) instead. Total tiles available: " << static_cast<int>(tiles.size()) << std::endl;
                row.push_back(0); // If invalid, use the first tile
            }
        }
        tileMap.push_back(row);
        rowIndex++;
    }

    for (const auto& row : tileMap) {
        for (int tileID : row) {
            std::cout << tileID << " ";
        }
        std::cout << std::endl;
    }

    mapHeight = tileMap.size();
    mapWidth = (mapHeight > 0) ? tileMap[0].size() : 0;

    std::cout << "Map size: " << mapWidth << " x " << mapHeight << std::endl;
}

// Render tiles on screen
void Map::showTiles(Graphic& graphic, int camX, int camY) {
    if (tiles.empty()) {
        std::cout << "Tileset is empty! (message from map)" << std::endl;
        return;
    }

    int colStart = camX / (tileSize * UPSCALE);
    int rowStart = camY / (tileSize * UPSCALE);
    int colEnd = colStart + (WINDOW_WIDTH / (tileSize * UPSCALE)) + 2;
    int rowEnd = rowStart + (WINDOW_HEIGHT / (tileSize * UPSCALE)) + 2;

    for (int row = rowStart; row < rowEnd; row++) {
        for (int col = colStart; col < colEnd; col++) {

            if (row < 0 || row >= mapHeight || col < 0 || col >= mapWidth) continue;

            int tileID = tileMap[row][col];
            if (tileID < 0 || tileID >= static_cast<int>(tiles.size())) continue;

            int screenX = (col * tileSize * UPSCALE) - camX;
            int screenY = (row * tileSize * UPSCALE) - camY;

            bool isVisible = (screenX + tileSize * UPSCALE > 0 && screenX < WINDOW_WIDTH && screenY + tileSize * UPSCALE > 0 && screenY < WINDOW_HEIGHT);

            if (!isVisible) continue;
            if (tileID == 0) {
                SDL_SetTextureAlphaMod(tiles[tileID], 0);
            }

            graphic.renderTextureKeepRatio(tiles[tileID], screenX, screenY, UPSCALE);

            if (tileID == 0) {
                SDL_SetTextureAlphaMod(tiles[tileID], 255);
            }
        }
    }
}

// Render the map
void Map::show(Graphic& graphic, int x, int y) {
    /* SDL_SetTextureAlphaMod(background.getCurrentCostume(), 150); */
    background.showBackground(background.getCurrentCostume(), x, y);
}