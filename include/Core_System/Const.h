#ifndef CONST_H
#define CONST_H

#include <SDL2/SDL.h>
#include <string>

// Kích thước cửa sổ
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// Kích thước player
constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;

// FPS
constexpr int FPS = 60;
constexpr int FRAME_DELAY = 1000 / FPS;

// Đường dẫn tài nguyên
const std::string WINDOW_TITLE = "RPG Game";
const std::string BACKGROUND_PATH = "assets/background/Grass.png";
const std::string PLAYER_SPRITE_PATH = "assets/player/idle.png";

// Tốc độ di chuyển của nhân vật
constexpr int PLAYER_SPEED = 5;

#endif // CONST_H
