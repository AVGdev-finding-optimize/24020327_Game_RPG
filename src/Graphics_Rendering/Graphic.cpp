#include "Graphics_Rendering/Graphic.h"

// Constructor
Graphic::Graphic() {
    window = nullptr;
    renderer = nullptr;
}

//Destructor

void Graphic::quitSDL() {
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

// Destructor
Graphic::~Graphic() {
    quitSDL() ;
}

// Khởi tạo SDL
bool Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error create window: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Chuẩn bị cảnh trước khi vẽ
void Graphic::prepareScene() {
    SDL_RenderClear(renderer);
}

// Hiển thị hình ảnh lên màn hình
void Graphic::presentScene() {
    SDL_RenderPresent(renderer);
}

// Load texture từ file
SDL_Texture* Graphic::loadTexture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cerr << "Error loading image: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Vẽ hình ảnh
void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}