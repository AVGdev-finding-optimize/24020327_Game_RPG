#ifndef CONST_H
#define CONST_H
#include <SDL2/SDL.h>
#include <string>

#define WINDOW_TITLE "RPG GAME"
#define BACKGROUND_PATH "D:/CODE/RPG_GAME/assets/background/Grass.png"
#define PALETTE_PATH "D:/CODE/RPG_GAME/assets/background/window.png"
#define HIGHLIGHT_PATH "D:/CODE/RPG_GAME/assets/tiles/Outline.png"
#define ROOM_PATH "D:/CODE/RPG_GAME/assets/player/Room.png"
#define PLAYER_SPRITE_PATH "D:/CODE/RPG_GAME/assets/player/idle0.png"
#define VILLAGE_MAP_PATH_LAYER_1 "D:/CODE/RPG_GAME/assets/map/Village_layer_1.txt"
#define VILLAGE_MAP_PATH_LAYER_2 "D:/CODE/RPG_GAME/assets/map/Village_layer_2.txt"
#define VILLAGE_MAP_PATH_LAYER_3 "D:/CODE/RPG_GAME/assets/map/Village_layer_3.txt"

// Logo
#define LOGO_PATH "D:/CODE/RPG_GAME/assets/background/logo.png"

//Music
#define MUSIC_VILLAGE_PATH "D:/CODE/RPG_GAME/assets/music/Background_Village_map.mp3"

// Size window
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int FRAME_DELAY = 16;
const int PALETTE_WIDTH = 250;
const int PALETTE_HEIGHT = 350;
const int MAX_PALETTE_ROWS = 9;
const int FADE_STEPS = 50;

// Player characteristics
const int PLAYER_SPEED = 4;
const int PLAYER_MAX_WIDTH = 0;
const int PLAYER_MAX_HEIGHT = 0;
const int TILE_0_ALPHA = 0;
const int TOTAL_COLS = 18;
const int TOTAL_ROWS = 30;
const int VIEW_COLS = 5;
const int VIEW_ROWS = 9;

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