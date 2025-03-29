#include "Map.h"
#include <iostream>
#include <algorithm>

// ---------- Code map generate ----------

// Render case block
Map::Map(Graphic& graphic) 
    : graphic(graphic), background(graphic, 100), tileSize(32), mapWidth(0), mapHeight(0) {
    tileMap.clear();
    tiles.clear();
}

Map::~Map() {
    for (auto tile : tiles) {
        SDL_DestroyTexture(tile);
    }
    SDL_DestroyTexture(palette);
    SDL_DestroyTexture(highlightTile);
    SDL_DestroyTexture(previewTile);
    tiles.clear();
}

// Background block
void Map::switchBackground(int index) {
    background.switchCostume(index);
}

bool Map::loadBackground(Graphic& graphic, const std::string& path) {
    SDL_Texture* bgTexture = graphic.loadTexture(path);
    if (bgTexture) {
        background.addCostume(bgTexture);
        return true; 
    } else {
        std::cerr << "ERROR: Failed to load background (message from map) " << path << std::endl;
        return false; 
    }
}

// Map setup block
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

    if (!tiles.empty()) {
        SDL_SetTextureAlphaMod(tiles[0], TILE_0_ALPHA);
    }

    highlightTile = graphic.loadTexture("D:/CODE/RPG_GAME/assets/tiles/Outline.png");
    if (!highlightTile) {
        std::cerr << "ERROR: Failed to load highlight tile (Outline.png)! (message from map)" << std::endl;
    }

    std::cerr << "🎉 Tiles loaded! Totals of tiles  (message from map): " << tiles.size() << std::endl;

    palette = graphic.loadTexture("D:/CODE/RPG_GAME/assets/background/window.png");
    if (!palette) {
        std::cerr << "ERROR: Failed to load editor window (Outline.png)! (message from map)" << std::endl;
    }
}

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

// Render map block
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

            bool isVisible = (screenX + tileSize * UPSCALE > 0 && screenX < WINDOW_WIDTH &&
                screenY + tileSize * UPSCALE > 0 && screenY < WINDOW_HEIGHT);
            if (!isVisible) continue;

            // Vẽ tile trước
            graphic.renderTextureKeepRatio(tiles[tileID], screenX, screenY, UPSCALE);
        }
    }
}

void Map::show(Graphic& graphic, int x, int y) {
    background.showBackground(background.getCurrentCostume(), x, y);
}

// --------- Code map editor ----------
void Map::saveMapToFile(const std::string& filePath) {
    if (mapEditor) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "ERROR: Cannot open file " << filePath << " for writing! (message from map)" << std::endl;
            return;
        }

        for (int row = 0; row < mapHeight; row++) {
            for (int col = 0; col < mapWidth; col++) {
                file << tileMap[row][col];
                if (col < mapWidth - 1) file << " ";
            }
            file << "\n";
        }

        file.close();
        std::cout << "Map saved to " << filePath << " successfully! (message from map)" << std::endl;
    }
}

void Map::updateMousePosition(int mouseX, int mouseY, int camX, int camY) {
    mouseTileX = (mouseX + camX) / (tileSize * UPSCALE);
    mouseTileY = (mouseY + camY) / (tileSize * UPSCALE);
    mousePosX = mouseX;
    mousePosY = mouseY;
}

void Map::showPalette() {
    if (!paletteOpen) {
        std::cerr << "ERROR: Cannot open palette editor! (message from map)" << std::endl;
        return;
    }

    int tilePerRow = 5;
    int tileSpacing = 1;
    int tileSizeScaled = tileSize * UPSCALE;
    int paletteX = WINDOW_WIDTH - ( tilePerRow * tileSizeScaled + (tilePerRow + 1) * 3);
    int paletteY = 0;

    paletteRect.x = paletteX;
    paletteRect.y = paletteY;
    paletteRect.w = PALETTE_WIDTH;
    paletteRect.h = PALETTE_HEIGHT;

    if (mapEditor && palette) {
        graphic.renderTextureKeepRatio(palette, paletteX, paletteY, UPSCALE);
    }

    int startRow = paletteOffset;
    int endRow = (startRow + MAX_PALETTE_ROWS < (int)((tiles.size() + tilePerRow - 1) / tilePerRow)) ? (startRow + MAX_PALETTE_ROWS) : ((int)((tiles.size() + tilePerRow - 1) / tilePerRow));

    for (int row = startRow; row < endRow; row++) {
        for (int col = 0; col < tilePerRow; col++) {
            int tileIndex = row * tilePerRow + col + 1;
            if (tileIndex >= static_cast<int>(tiles.size())) break;

            int tileX = paletteX + 18 + col * (tileSizeScaled + tileSpacing);
            int tileY = paletteY + 20 + (row - paletteOffset) * (tileSizeScaled + tileSpacing);

            SDL_Texture* tileTexture = tiles[tileIndex];
            if (tileTexture) {
                graphic.renderTextureKeepRatio(tileTexture, tileX, tileY, UPSCALE);
            }
        }
    }
    
    std::cout << "Palette is openning! (message from map)" << std::endl;
}

void Map::setPreviewTile() {
    if (eraseTile && mapEditor) paintbrush = 0;
    if (paintbrush >= 0 && paintbrush < static_cast<int>(tiles.size())) {
        previewTile = tiles[paintbrush];
        selectedTileID = paintbrush;
    } else {
        previewTile = nullptr;
        selectedTileID = 0;
    }
}

void Map::highlightCursor(int camX, int camY) {
    bool mouseInPalette = (mousePosX >= paletteRect.x && mousePosX < paletteRect.x + paletteRect.w && 
                           mousePosY >= paletteRect.y && mousePosY < paletteRect.y + paletteRect.h);
    if (mouseInPalette) return;

    int highlightX = (mouseTileX * tileSize * UPSCALE) - camX;
    int highlightY = (mouseTileY * tileSize * UPSCALE) - camY;

    if (highlightTile) {
        graphic.renderTextureKeepRatio(highlightTile, highlightX, highlightY, UPSCALE);
    }

    setPreviewTile();
    if (previewTile) {
        graphic.renderTextureKeepRatio(previewTile, highlightX + 4, highlightY + 4, UPSCALE);
    }
}

void Map::handleMouseWheelPalette(int yScroll) {
    if (!paletteOpen) return; 

    int maxRows = (tiles.size() + 4) / 5;
    int visibleRows = ( maxRows < MAX_PALETTE_ROWS ) ? maxRows : MAX_PALETTE_ROWS;
    int maxOffset = (0 > maxRows - visibleRows) ? 0 : maxRows - visibleRows;

    paletteOffset = clamp(paletteOffset - yScroll, 0, maxOffset);
}

void Map::handleMousePalette(int button) {
    if (!mapEditor || !paletteOpen) return;

    bool mouseInPalette = (mousePosX > paletteRect.x && mousePosY > paletteRect.y);

    if (!mouseInPalette) {
        if (button == SDL_BUTTON_LEFT) {
            selectedTileX = mouseTileX;
            selectedTileY = mouseTileY;
            tileMap[selectedTileY][selectedTileX] = paintbrush; 
        }
        return;
    } else {
        int paletteColumns = 5;

        int col = clamp((mousePosX - paletteRect.x - 18 + tileSize) / (tileSize * UPSCALE + 1) + 1, 1, 5);
        int row = (mousePosY - paletteRect.y - 18 + paletteOffset * (tileSize * UPSCALE + 1)) / (tileSize * UPSCALE);
    
        int newSelectedTile = row * paletteColumns + col;
    
        if (newSelectedTile >= 0 && newSelectedTile < static_cast<int>(tiles.size())) {
            selectedTile = newSelectedTile;
            paintbrush = selectedTile;
        }
    }
}

// ---------- Text engine ----------
void Map::displayPaintBrushTileID(TextEngine* textEngine) {
    if (!textEngine) {
        std::cerr << "TextEngine not initialized!" << std::endl;
        return;
    }

    if (paintbrush < 0 || paintbrush >= static_cast<int>(tiles.size())) {
        std::cerr << "Invalid paintBrush tile ID: " << paintbrush << std::endl;
        return;
    }

    std::string tileText = "Tile ID: " + std::to_string(paintbrush);
    textEngine->showText(tileText, WINDOW_WIDTH - 120, WINDOW_HEIGHT - 50, WHITE_COLOR);
}

int Map::clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

