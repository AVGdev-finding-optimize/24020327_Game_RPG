#include "Colision.h"
#include <fstream>
#include <iostream>

Colision::Colision(Graphic& graphic) {
    redPoint = graphic.loadTexture(RED_POINT_PATH);
    if (!redPoint) {
        std::cerr << "ERROR: Failed to load red point texture (message from colision)" << std::endl;
    }
    whitePoint = graphic.loadTexture(WHITE_POINT_PATH);
    if (!whitePoint) {
        std::cerr << "ERROR: Failed to load white point texture (message from colision)" << std::endl;
    }
}

Colision::~Colision() {
    SDL_DestroyTexture(redPoint);
    SDL_DestroyTexture(whitePoint);
}

void Colision::setPinButtonClicked(bool clicked) {
    pinButtonClicked = clicked;
}

void Colision::loadPinData(const std::string& filePath) {
    tilePinData.clear();
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> pins;
        for (char c : line) {
            pins.push_back(c == '1' ? 1 : 0);
        }
        while (pins.size() < 9) pins.push_back(0);
        tilePinData.push_back(pins);
    }
    std::cout << "Pin size: " << tilePinData.size() << std::endl;
    if (tilePinData.empty()) {
        std::cerr << "ERROR: No pin data loaded! (message from colision)" << std::endl;
    } else {
        std::cout << "Pin data loaded successfully! (message from colision)" << std::endl;
    }
    file.close();
}

void Colision::savePinData(const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Cannot open file for writing: " << filePath << std::endl;
        return;
    }

    for (const std::vector<int>& pinLine : tilePinData) {
        for (int pin : pinLine) {
            outFile << pin;
        }
        outFile << '\n';
    }

    outFile.close();
}

std::vector<int> Colision::getPinData(int tileID) const {
    if (tileID >= 0 && tileID < (int)tilePinData.size()) {
        return tilePinData[tileID];
    }
    return std::vector<int>(9, 0);
}

int Colision::getTileIDAt(int mapX, int mapY, const std::vector<std::vector<int>>& tileMap) const {
    if (mapY >= 0 && mapY < (int)tileMap.size() && mapX >= 0 && mapX < (int)tileMap[0].size()) {
        return tileMap[mapY][mapX];
    }
    return -1;
}

int Colision::getPinIndexFromMouse(int mouseX, int mouseY, int x, int y, int tileSize) {
    int subSize = tileSize / 3;
    int localX = mouseX - x;
    int localY = mouseY - y;
    if (localX < 0 || localY < 0 || localX >= tileSize || localY >= tileSize) return -1;

    int col = localX / subSize;
    int row = localY / subSize;
    return row * 3 + col;
}

void Colision::drawPinPalette(SDL_Renderer* renderer, int tileID, int x, int y) {
    if (tileID < 0 || tileID >= (int)tilePinData.size()) return;
    std::cerr << "Drawing pin palette for tile ID: " << tileID << std::endl;
    int subSize = 64 / 3;
    std::vector<int>& pins = tilePinData[tileID];

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (int i = 0; i < 9; ++i) {
        int row = i / 3;
        int col = i % 3;
        int px = x + col * subSize;
        int py = y + row * subSize;

        SDL_Rect dest = { px, py, subSize, subSize };
        SDL_Texture* point = pins[i] ? redPoint : whitePoint;
        SDL_SetTextureAlphaMod(point, 255);
        SDL_SetTextureBlendMode(point, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, point, nullptr, &dest);

        if (pinButtonClicked && getPinIndexFromMouse(mouseX, mouseY, x, y) == i) {
            pins[i] = 1 - pins[i];
        }
    }
}

