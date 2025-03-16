#include "Graphics_Rendering/Graphic.h"

Graphic::Graphic() {}

Graphic::~Graphic() {
    // Giải phóng tài nguyên để tránh rò rỉ bộ nhớ
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

bool Graphic::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error init SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cerr << "Error create window: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cerr << "Error create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Graphic::quitSDL() {
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* Graphic::loadTexture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cout << "Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return newTexture;
}

void Graphic::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Rect Graphic::returnSize(SDL_Texture* texture, double ratio) {
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.w *= ratio;
    rect.h *= ratio;
    return rect;
}

void Graphic::prepareSence() {
    SDL_RenderClear(renderer);
}

void Graphic::presentSence() {
    SDL_RenderPresent(renderer);
}