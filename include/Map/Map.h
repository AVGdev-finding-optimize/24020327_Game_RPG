#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
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

    void loadBackground(Graphic& graphic, const std::string& path);
    void switchBackground(int index);
    void loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths);
    void setMapLayout(const std::vector<std::vector<int>>& layout);
    void show(Graphic& graphic, int x, int y);
};

#endif