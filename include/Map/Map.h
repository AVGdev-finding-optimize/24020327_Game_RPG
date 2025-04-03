#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"
#include "Graphics_Rendering/Textengine.h"
#include "Core_System/Const.h"

class Map {
private:
    std::vector<SDL_Texture*> tiles; // Tileset textures
    Graphic& graphic;
    Animation background;
    int tileSize; // Size of each tile
    int mapWidth, mapHeight; // Map dimensions (in tiles)
    std::vector<std::vector<int>> tileMap; // 2D tilemap layout
    
    //map editor
    bool mapEditor = 1;
    SDL_Texture* palette;
    SDL_Texture* highlightTile;
    SDL_Texture* previewTile = nullptr;
    int mouseTileX, mouseTileY;
    int selectedTileX, selectedTileY;
    int paintbrush = -1;
    int selectedTileID = 0;
    int paletteOffset = 0;
    int mousePosX, mousePosY;

public:
    Map(Graphic& graphic);
    ~Map();

    // return const block
    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }
    int getTileSize() const { return tileSize; }
    bool isMapEditorActive() const { return mapEditor; }
    bool isPaletteOpen() const { return paletteOpen; }

    // logic and flags block
    bool eraseTile = 0;
    bool paletteOpen = 0;

    // generate block
    bool loadBackground(Graphic& graphic, const std::string& path);
    void switchBackground(int index);
    void loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths);
    void showTiles(Graphic& graphic, int camX, int camY);
    void setMapLayoutFromFile(const std::string& filename);
    void saveMapToFile(const std::string& filePath);

    // map edit block
    int selectedTile; 
    SDL_Rect paletteRect;
    void setPreviewTile();
    void show(Graphic& graphic, int x, int y);
    void showPalette();
    void handleMouseWheelPalette(int yScroll);
    void updateMousePosition(int mouseX, int mouseY, int camX, int camY);
    void handleMousePalette(int button);
    void highlightCursor(int camX, int camY);
    int clamp(int value, int min, int max);

    // text engine
    void displayPaintBrushTileID(TextEngine* textEngine);
};

#endif