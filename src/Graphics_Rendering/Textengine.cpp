#include "TextEngine.h"
#include <iostream>

TextEngine::TextEngine(SDL_Renderer* renderer) : renderer(renderer), font(nullptr) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
}

TextEngine::~TextEngine() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

bool TextEngine::loadFont(const std::string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << fontPath << " SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Texture* TextEngine::renderText(const std::string& text, SDL_Color color) {
    if (!font) {
        std::cerr << "Font not loaded!" << std::endl;
        return nullptr;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void TextEngine::showText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Texture* texture = renderText(text, color);
    if (!texture) return;

    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    SDL_DestroyTexture(texture);
}