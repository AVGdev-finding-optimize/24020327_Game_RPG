#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Core_System/Const.h"

class Map {
private:
    std::vector<SDL_Texture*> tiles; // Tileset textures
    Graphic& graphic;
    Animation background;
    int tileSize; // Size of each tile
    int mapWidth, mapHeight; // Map dimensions (in tiles)
    std::vector<std::vector<int>> tileMap; // 2D tilemap layout

public:
    Map(Graphic& graphic);
    ~Map();

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    int getTileSize() const { return tileSize; }

    bool loadBackground(Graphic& graphic, const std::string& path);
    void switchBackground(int index);
    void loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths);
    void showTiles(Graphic& graphic, int camX, int camY);
    void setMapLayoutFromFile(const std::string& filename);
    void show(Graphic& graphic, int x, int y);
};

#endif