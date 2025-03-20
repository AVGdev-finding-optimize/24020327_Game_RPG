#include "Graphics_Rendering/Graphic.h"

// Constructor
Graphic::Graphic() : window(nullptr), renderer(nullptr) {}

// Destructor
Graphic::~Graphic() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

// Khởi tạo SDL, cửa sổ và renderer
bool Graphic::initSDL(int width, int height, const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// Load texture từ file ảnh
SDL_Texture* Graphic::loadTexture(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << filePath << " SDL_Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

// Render texture to screen with aspect ratio
void Graphic::renderTextureKeepRatio(SDL_Texture* texture, int x, int y, int maxWidth, int maxHeight) {
    if (!texture) {
        std::cerr << "ERROR: Texture is NULL!" << std::endl;
        return;
    }

    int originalW, originalH;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &originalW, &originalH) != 0) {
        std::cerr << "ERROR: Cannot query texture: " << SDL_GetError() << std::endl;
        return;
    }

    if (maxWidth == 0) maxWidth = originalW;
    if (maxHeight == 0) maxHeight = originalH;

    float scaleFactor = std::min((float)maxWidth / originalW, (float)maxHeight / originalH);

    int newW = static_cast<int>(originalW * scaleFactor);
    int newH = static_cast<int>(originalH * scaleFactor);

    SDL_Rect dstRect = { x, y, newW, newH };
    
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

// Render background
void Graphic::renderBackground(SDL_Texture* texture, int x, int y) {
    if (!texture) {
        std::cerr << "ERROR: Background texture is NULL!" << std::endl;
        return;
    }

    int originalW, originalH;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &originalW, &originalH) != 0) {
        std::cerr << "ERROR: Cannot query texture: " << SDL_GetError() << std::endl;
        return;
    }

    int scaledW = originalW * 2;
    int scaledH = originalH * 2;

    SDL_Rect dstRect = { x, y, scaledW, scaledH };

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

// Clear screen before rendering
void Graphic::prepareScene() {
    SDL_RenderClear(renderer);
}

// Hiển thị nội dung đã render lên màn hình
void Graphic::presentScene() {
    SDL_RenderPresent(renderer);
}

// Getter lấy renderer
SDL_Renderer* Graphic::getRenderer() const {
    return renderer;
}

// Getter lấy window
SDL_Window* Graphic::getWindow() const {
    return window;
}