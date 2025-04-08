#include "Map.h"
#include <iostream>
#include <algorithm>

// ---------- Code map generate ----------

// Render case block
Map::Map(Graphic& graphic) 
    : graphic(graphic), background(graphic, 100), tileSize(32), mapWidth(0), mapHeight(0) {
    tileMapLayerA.clear();
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

    tileMapLayerA.clear();
    
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
        tileMapLayerA.push_back(row);
        rowIndex++;
    }

    for (const auto& row : tileMapLayerA) {
        for (int tileID : row) {
            std::cout << tileID << " ";
        }
        std::cout << std::endl;
    }

    mapHeight = tileMapLayerA.size();
    mapWidth = (mapHeight > 0) ? tileMapLayerA[0].size() : 0;

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

            int tileID = tileMapLayerA[row][col];
            if (tileID < 0 || tileID >= static_cast<int>(tiles.size())) continue;

            int screenX = (col * tileSize * UPSCALE) - camX;
            int screenY = (row * tileSize * UPSCALE) - camY;

            bool isVisible = (screenX + tileSize * UPSCALE > 0 && screenX < WINDOW_WIDTH &&
                screenY + tileSize * UPSCALE > 0 && screenY < WINDOW_HEIGHT);
            if (!isVisible) continue;

            int texWidth, texHeight;
            SDL_QueryTexture(tiles[tileID], nullptr, nullptr, &texWidth, &texHeight);
            if (tiles[tileID]) {
                if (texWidth < tileSize && (tileID == 67 || tileID == 85)) {
                    graphic.renderTextureKeepRatio(tiles[tileID], screenX + (tileSize - texWidth) * UPSCALE, screenY, UPSCALE);
                } else {
                    graphic.renderTextureKeepRatio(tiles[tileID], screenX, screenY, UPSCALE);
                }
            }
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
                file << tileMapLayerA[row][col];
                if (col < mapWidth - 1) file << " ";
            }
            file << "\n";
        }

        file.close();
        std::cout << "Map saved to " << filePath << " successfully! (message from map)" << std::endl;
    }
}

void Map::showPalette() {
    if (!paletteOpen) {
        std::cerr << "ERROR: Cannot open palette editor! (message from map)" << std::endl;
        return;
    }

    const int tileSpacing = 1;
    const int tileSizeScaled = tileSize * UPSCALE;

    int paletteX = WINDOW_WIDTH - (VIEW_COLS * tileSizeScaled + (VIEW_COLS + 1) * tileSpacing);
    int paletteY = 20;

    paletteRect = { paletteX, paletteY,
        VIEW_COLS * (tileSizeScaled + tileSpacing) + tileSpacing,
        VIEW_ROWS * (tileSizeScaled + tileSpacing) + tileSpacing
    };

    if (mapEditor && palette) {
        graphic.renderTextureKeepRatio(palette, paletteX - 20, paletteY - 20, UPSCALE);
    }

    int tileIndex = 0;
    int saveX, saveY;
    for (int row = 0; row < VIEW_ROWS; ++row) {
        for (int col = 0; col < VIEW_COLS; ++col) {
            int globalRow = paletteOffsetY + row;
            int globalCol = paletteOffsetX + col + 1;
            tileIndex = globalRow * TOTAL_COLS + globalCol;

            if (tileIndex == 0 || tileIndex >= static_cast<int>(tiles.size())) continue;

            int tileX = paletteX + tileSpacing + col * (tileSizeScaled + tileSpacing);
            int tileY = paletteY + tileSpacing + row * (tileSizeScaled + tileSpacing);
            
            if (tileIndex == selectedTile) {
                saveX = tileX;
                saveY = tileY;
            }

            SDL_Texture* tileTexture = tiles[tileIndex];
            if (!tileTexture) continue;

            SDL_SetTextureAlphaMod(tileTexture, 255);

            int texWidth, texHeight;
            SDL_QueryTexture(tileTexture, nullptr, nullptr, &texWidth, &texHeight);

            if (texWidth < tileSize && (tileIndex == 67 || tileIndex == 85)) {
                graphic.renderTextureKeepRatio(tileTexture, tileX + (tileSize - texWidth) * UPSCALE, tileY, UPSCALE);
            } else {
                graphic.renderTextureKeepRatio(tileTexture, tileX, tileY, UPSCALE);
            }
        }
    }
    if (tileIndex == selectedTile) {
        graphic.renderTextureKeepRatio(highlightTile, saveX, saveY, UPSCALE);
    }
    std::cout << "Palette is opening! (message from map)" << std::endl;
}

void Map::setPreviewTile() {
    if (mapEditor) {
        if (eraseTile) {
            previewTile = tiles[0]; 
            selectedTileID = 0;
            paintbrush = 0;
            return;
        } else {
            if (paintbrush > 0 && paintbrush < static_cast<int>(tiles.size())) {
                previewTile = tiles[paintbrush];  
                selectedTileID = paintbrush; 
            } else {
                previewTile = nullptr;
                selectedTileID = 0;  
            }
        }
    }
}

void Map::highlightCursor(int camX, int camY) {
    bool mouseInPalette = (mousePosX >= paletteRect.x && mousePosX < paletteRect.x + paletteRect.w &&
                           mousePosY >= paletteRect.y && mousePosY < paletteRect.y + paletteRect.h);
    if (paletteOpen && mouseInPalette) {
        return;
    }

    int highlightX = (mouseTileX - paletteOffsetX) * tileSize * UPSCALE - camX;
    int highlightY = (mouseTileY - paletteOffsetY) * tileSize * UPSCALE - camY;

    highlightX += (paletteOffsetX * tileSize * UPSCALE);
    highlightY += (paletteOffsetY * tileSize * UPSCALE);

    if (highlightTile) {
        graphic.renderTextureKeepRatio(highlightTile, highlightX, highlightY, UPSCALE);
    }

    setPreviewTile();
    if (previewTile) {
        if (previewTile == tiles[0]) {
            SDL_SetTextureAlphaMod(previewTile, 0);
        } else {
            SDL_SetTextureAlphaMod(previewTile, 120);
        }
        graphic.renderTextureKeepRatio(previewTile, highlightX + 4, highlightY + 4, UPSCALE);
    }
}

void Map::updateMousePosition(int mouseX, int mouseY, int camX, int camY) {
    mousePosX = mouseX;
    mousePosY = mouseY;
    mouseTileX = (mouseX + camX) / (tileSize * UPSCALE);
    mouseTileY = (mouseY + camY) / (tileSize * UPSCALE);
}

void Map::handleMouseWheelPalette(int scroll) {
    if (!paletteOpen) return;

    const Uint16 mod = SDL_GetModState();

    if (mod & KMOD_SHIFT) {  
        int maxOffsetX = TOTAL_COLS - VIEW_COLS;
        paletteOffsetX = clamp(paletteOffsetX - scroll, 0, maxOffsetX);

        std::cout << "Horizontal Scroll - Offset X: " << paletteOffsetX << std::endl;
    } else {
        int maxOffsetY = TOTAL_ROWS - VIEW_ROWS;
        paletteOffsetY = clamp(paletteOffsetY - scroll, 0, maxOffsetY);

        std::cout << "Vertical Scroll - Offset Y: " << paletteOffsetY << std::endl;
    }
}

void Map::handleMousePalette(int button) { 
    if (!mapEditor || !paletteOpen) return;

    bool mouseInPalette = (mousePosX >= paletteRect.x && mousePosY >= paletteRect.y &&
                           mousePosX < paletteRect.x + paletteRect.w &&
                           mousePosY < paletteRect.y + paletteRect.h);

    int tileSpacing = 1;
    int tileSizeScaled = tileSize * UPSCALE;

    if (!mouseInPalette) {
        if (button == SDL_BUTTON_LEFT) {
            if (selectedTileY >= 0 && selectedTileY < (int)tileMapLayerA.size() &&
                selectedTileX >= 0 && selectedTileX < (int)tileMapLayerA[0].size()) {
                
                selectedTileX = mouseTileX;
                selectedTileY = mouseTileY;
                
                if (!isDragging) {
                    prevMouseTileX = selectedTileX;
                    prevMouseTileY = selectedTileY;
                    dragBasePaintbrush = paintbrush;  
                    isDragging = true;
                }

                int newPaintbrush = paintbrush;

                if (dragTile) {
                    int deltaX = selectedTileX - prevMouseTileX;
                    int deltaY = selectedTileY - prevMouseTileY;
                    newPaintbrush = dragBasePaintbrush + deltaX + deltaY * 18;

                    if (newPaintbrush < 0 || newPaintbrush >= static_cast<int>(tiles.size())) {
                        newPaintbrush = dragBasePaintbrush;
                    }

                    paintbrush = newPaintbrush;
                }

                tileMapLayerA[selectedTileY][selectedTileX] = paintbrush;
                SDL_SetTextureAlphaMod(previewTile, 255);
            }
        }
        return;
    }

    int localX = mousePosX - paletteRect.x - tileSpacing;
    int localY = mousePosY - paletteRect.y - tileSpacing;

    int col = localX / (tileSizeScaled + tileSpacing);
    int row = localY / (tileSizeScaled + tileSpacing);

    if (col < 0 || col >= VIEW_COLS || row < 0 || row >= VIEW_ROWS) return;

    int globalCol = paletteOffsetX + col;
    int globalRow = paletteOffsetY + row;

    int tileIndex = globalRow * TOTAL_COLS + globalCol + 1;

    if (tileIndex >= 0 && tileIndex < static_cast<int>(tiles.size())) {
        selectedTile = tileIndex;
        paintbrush = tileIndex;
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
    textEngine->showText(tileText, WINDOW_WIDTH - PALETTE_WIDTH, WINDOW_HEIGHT - 50, WHITE_COLOR);
    std::string eraseText = eraseTile ? "Erase mode: ON" : "Erase mode: OFF";
    textEngine->showText(eraseText, WINDOW_WIDTH - PALETTE_WIDTH, WINDOW_HEIGHT - 70, WHITE_COLOR);
    std::string dragText = dragTile ? "Drag mode: ON" : "Drag mode: OFF";
    textEngine->showText(dragText, WINDOW_WIDTH - PALETTE_WIDTH, WINDOW_HEIGHT - 90, WHITE_COLOR);
    graphic.presentScene();
}

int Map::clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

