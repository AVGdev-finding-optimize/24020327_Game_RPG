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
void Map::setMapLayout(const std::vector<std::vector<int>>& layout) {
    if (layout.empty() || layout[0].empty()) {
        std::cerr << "ERROR: Invalid map layout" << std::endl;
        return;
    }
    tileMap = layout;
    mapHeight = layout.size();
    mapWidth = layout[0].size();
}

// Render the map
void Map::show(Graphic& graphic, int x, int y) {
    background.showBackground(background.getCurrentCostume(), x, y);
}
