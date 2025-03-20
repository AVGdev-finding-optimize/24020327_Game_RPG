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
void Map::loadBackground(Graphic& graphic, const std::string& path) {
    SDL_Texture* bgTexture = graphic.loadTexture(path);
    if (bgTexture) {
        background.addCostume(bgTexture);
    } else {
        std::cerr << "ERROR: Failed to load background " << path << std::endl;
    }
}

// Load tileset from file paths
void Map::loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths) {
    for (const auto& path : tilePaths) {
        SDL_Texture* tile = graphic.loadTexture(path.c_str());
        if (tile) {
            tiles.push_back(tile);
        } else {
            std::cerr << "ERROR: Failed to load tile " << path << std::endl;
        }
    }
}

// Set map layout using a 2D vector
void Map::setMapLayoutFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR: Cannot open map file " << filename << std::endl;
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
            if (tileID >= 0 && tileID < static_cast<int>(tiles.size())) { 
                row.push_back(tileID);
            } else {
                std::cerr << "WARNING: Tile ID " << tileID << " is out of range!" << std::endl;
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
}

// Render tiles on screen
void Map::showTiles(Graphic& graphic, int camX, int camY) {
    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            int tileID = tileMap[row][col];

            // If tileID is -1, it means no tile should be rendered
            if (tileID == -1) continue;

            if (tileID >= 0 && tileID < static_cast<int>(tiles.size())) {
                int screenX = col * tileSize - camX;
                int screenY = row * tileSize - camY;

                if (screenX + tileSize > 0 && screenX < WINDOW_WIDTH && screenY + tileSize > 0 && screenY < WINDOW_HEIGHT) {
                    
                    if (tileID >= 0 && tileID < static_cast<int>(tiles.size())) {
                        graphic.renderTextureKeepRatio(tiles[tileID], screenX, screenY, tileSize, tileSize);
                    }
                }

            }
        }
    }
}

// Render the map
void Map::show(Graphic& graphic, int x, int y) {
    background.showBackground(background.getCurrentCostume(), x, y);
}
