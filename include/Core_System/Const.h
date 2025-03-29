#ifndef CONST_H
#define CONST_H
#include <SDL2/SDL.h>
#include <string>

// Define constants
#define WINDOW_TITLE "RPG GAME"
#define BACKGROUND_PATH "D:/CODE/RPG_GAME/assets/background/Grass.png"
#define ROOM_PATH "D:/CODE/RPG_GAME/assets/player/Room.png"
#define PLAYER_SPRITE_PATH "D:/CODE/RPG_GAME/assets/player/idle0.png"
#define VILLAGE_MAP_PATH "D:/CODE/RPG_GAME/assets/map/map_70x70.txt"

// Kích thước cửa sổ
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int FRAME_DELAY = 16;
const int PALETTE_WIDTH = 250;
const int PALETTE_HEIGHT = 350;
const int MAX_PALETTE_ROWS = 9;

// Cấu hình nhân vật
const int PLAYER_SPEED = 4;
const int PLAYER_MAX_WIDTH = 0;
const int PLAYER_MAX_HEIGHT = 0;

// Scolling background
const int CAMERA_MARGIN_X = 100;
const int CAMERA_MARGIN_Y = 75;
const int TILE_0_ALPHA = 0;

// Size img
const int UPSCALE = 2;

// Colors
const SDL_Color CYAN_COLOR = {0, 255, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0, 255};
const SDL_Color YELLOW_COLOR = {255, 255, 0, 255};
const SDL_Color LIME_COLOR = {0, 255, 0, 255};
const SDL_Color PURPLE_COLOR = {128, 0, 128, 255};
const SDL_Color RED_COLOR = {255, 0, 0, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0, 255};
const SDL_Color GREEN_COLOR = {0, 128, 0, 255};

#endif // CONST_H