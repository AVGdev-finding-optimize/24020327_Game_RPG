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
    std::vector<SDL_Texture*> tiles;
    Graphic& graphic;
    Animation background;
    int tileSize;
    int mapWidth, mapHeight;
    std::vector<std::vector<int>> tileMapLayerA;
    std::vector<std::vector<int>> tileMapLayerB;
    std::vector<std::vector<int>> tileMapLayerC;
    
    //map editor
    bool mapEditor = true;
    SDL_Texture* palette;
    SDL_Texture* highlightTile;
    SDL_Texture* previewTile = nullptr;
    int mouseTileX, mouseTileY;
    int selectedTileX, selectedTileY;
    int paintbrush = 0;
    int selectedTileID = 0;
    int paletteOffsetX = 0;
    int paletteOffsetY = 0;
    int dragX = 0;
    int dragY = 0;
    int prevMouseTileX = 0;
    int prevMouseTileY = 0;
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
    bool eraseTile = false;
    bool paletteOpen = false;
    bool dragTile = false;
    bool isDragging = false;
    bool onionMode = false;
    int dragBasePaintbrush = 0;
    int layer = 1;

    // generate block
    bool loadBackground(Graphic& graphic, const std::string& path);
    void switchBackground(int index);
    void loadTileset(Graphic& graphic, const std::vector<std::string>& tilePaths);
    void showTiles(Graphic& graphic, int camX, int camY, int layerIndex);
    void setMapLayoutFromFile(const std::string& filename, const int layoutIndex = 1);
    void saveMapToFile(const std::string& filePath, const int layoutIndex = 1);

    // map edit block
    int selectedTile; 
    SDL_Rect paletteRect;
    SDL_Rect tileRect;
    void setPreviewTile();
    void show(Graphic& graphic, int x, int y);
    void showPalette();
    
    void highlightCursor(int camX, int camY);
    
    void handleMouseWheelPalette(int scroll);
    void handleMousePalette(int button);
    void updateMousePosition(int mouseX, int mouseY, int camX, int camY);
    
    int clamp(int value, int min, int max);

    // text engine
    void displayPaintBrushTileID(TextEngine* textEngine);
};

#endif