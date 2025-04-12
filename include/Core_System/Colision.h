#ifndef COLISION_H
#define COLISION_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Graphics_Rendering/Graphic.h"
#include "Graphics_Rendering/Animation.h"

#define WHITE_POINT_PATH "assets/tiles/white_point.png"
#define RED_POINT_PATH "assets/tiles/red_point.png"

class Colision {
private:
    std::vector<std::vector<int>> tilePinData;
    SDL_Texture* redPoint;
    SDL_Texture* whitePoint;
    bool pinButtonClicked = false;

    int getPinIndexFromMouse(int mouseX, int mouseY, int x, int y, int tileSize = 64);

public:
    Colision(Graphic& graphic);
    ~Colision();
    
    void setPinButtonClicked(bool clicked);
    
    void loadPinData(const std::string& filePath);
    void savePinData(const std::string& filePath);
    std::vector<int> getPinData(int tileID) const;
    void drawPinPalette(SDL_Renderer* renderer, int tileID, int x, int y);
    int getTileIDAt(int mapX, int mapY, const std::vector<std::vector<int>>& tileMap) const;
};

#endif