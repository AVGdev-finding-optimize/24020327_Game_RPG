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
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FRAME_DELAY = 16;

// Cấu hình nhân vật
const int PLAYER_SPEED = 4;
const int PLAYER_MAX_WIDTH = 0;
const int PLAYER_MAX_HEIGHT = 0;

// Scolling background
const int CAMERA_MARGIN_X = 100;
const int CAMERA_MARGIN_Y = 75;

// Kích thước img
const int UPSCALE = 2;
#endif // CONST_H