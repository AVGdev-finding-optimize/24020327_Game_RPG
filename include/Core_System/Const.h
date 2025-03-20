#ifndef CONST_H
#define CONST_H

#include <SDL2/SDL.h>
#include <string>

// Kích thước cửa sổ
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// Kích thước player
constexpr int PLAYER_MAX_WIDTH = 0;
constexpr int PLAYER_MAX_HEIGHT = 0;

// FPS
constexpr int FPS = 60;
constexpr int FRAME_DELAY = 1000 / FPS;

// Đường dẫn tài nguyên
const std::string WINDOW_TITLE = "RPG Game";
const std::string BACKGROUND_PATH = "assets/background/Grass.png";
const std::string ROOM_PATH = "assets/player/Room.png";
const std::string PLAYER_SPRITE_PATH = "assets/player/idle.png";

// Tốc độ di chuyển của nhân vật
constexpr int PLAYER_SPEED = 4;

// Biên camera
constexpr int CAMERA_MARGIN_X = 100;
constexpr int CAMERA_MARGIN_Y = 75;

#endif // CONST_H