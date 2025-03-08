#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_SIZE = 20;
const int SNAKE_SPEED = 150;

struct Point {
    int x, y;
};

class SnakeGame {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Point> snake;
    Point apple;
    Point rocket;
    int score;
    int applesEaten;
    bool running;
    bool gameOver;
    int dirX, dirY;
    bool rocketActive;
    Point rocketDirection;
    Uint32 lastRocketTime;
    int minRocketSpawnTime;
    int maxRocketSpawnTime;
    Point target;
    bool movingToTarget;

public:
    SnakeGame() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        resetGame();
    }

    ~SnakeGame() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void resetGame() {
        snake = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {SCREEN_WIDTH / 2 - GRID_SIZE, SCREEN_HEIGHT / 2}};
        apple = {rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE, rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE};
        rocketActive = false;
        score = 0;
        applesEaten = 0;
        running = true;
        gameOver = false;
        dirX = GRID_SIZE;
        dirY = 0;
        target = snake[0];
        movingToTarget = false;
        lastRocketTime = SDL_GetTicks();
        minRocketSpawnTime = 5000;
        maxRocketSpawnTime = 30000;
    }

    void clearScreen() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    void spawnRocket() {
        int edge = rand() % 4;
        if (edge == 0) { rocket = {rand() % SCREEN_WIDTH, 0}; }
        else if (edge == 1) { rocket = {rand() % SCREEN_WIDTH, SCREEN_HEIGHT - GRID_SIZE}; }
        else if (edge == 2) { rocket = {0, rand() % SCREEN_HEIGHT}; }
        else { rocket = {SCREEN_WIDTH - GRID_SIZE, rand() % SCREEN_HEIGHT}; }
        rocketDirection = {(snake[0].x - rocket.x) / 20, (snake[0].y - rocket.y) / 20};
        rocketActive = true;
        lastRocketTime = SDL_GetTicks();
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                target.x = (event.button.x / GRID_SIZE) * GRID_SIZE;
                target.y = (event.button.y / GRID_SIZE) * GRID_SIZE;
                movingToTarget = true;
            }
        }
    }

    void update() {
        if (gameOver) return;

        if (movingToTarget) {
            if (snake[0].x < target.x) { dirX = GRID_SIZE; dirY = 0; }
            else if (snake[0].x > target.x) { dirX = -GRID_SIZE; dirY = 0; }
            else if (snake[0].y < target.y) { dirX = 0; dirY = GRID_SIZE; }
            else if (snake[0].y > target.y) { dirX = 0; dirY = -GRID_SIZE; }
        }
        
        Point newHead = {snake[0].x + dirX, snake[0].y + dirY};
        
        if (newHead.x < 0 || newHead.x >= SCREEN_WIDTH || newHead.y < 0 || newHead.y >= SCREEN_HEIGHT) {
            gameOver = true;
            return;
        }
        
        for (auto& segment : snake) {
            if (segment.x == newHead.x && segment.y == newHead.y) {
                gameOver = true;
                return;
            }
        }
        
        snake.insert(snake.begin(), newHead);
        
        if (newHead.x == apple.x && newHead.y == apple.y) {
            apple = {rand() % (SCREEN_WIDTH / GRID_SIZE) * GRID_SIZE, rand() % (SCREEN_HEIGHT / GRID_SIZE) * GRID_SIZE};
            score++;
            applesEaten++;
        } else {
            snake.pop_back();
        }
        
        Uint32 currentTime = SDL_GetTicks();
        if (!rocketActive && currentTime - lastRocketTime >= minRocketSpawnTime + rand() % (maxRocketSpawnTime - minRocketSpawnTime)) {
            spawnRocket();
            if (maxRocketSpawnTime > 10000) {
                maxRocketSpawnTime -= 1000;
            }
        }
        
        if (rocketActive) {
            rocket.x += rocketDirection.x;
            rocket.y += rocketDirection.y;
            if (newHead.x == rocket.x && newHead.y == rocket.y) {
                gameOver = true;
            }
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (auto& segment : snake) {
            SDL_Rect rect = {segment.x, segment.y, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect appleRect = {apple.x, apple.y, GRID_SIZE, GRID_SIZE};
        SDL_RenderFillRect(renderer, &appleRect);

        if (rocketActive) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_Rect rocketRect = {rocket.x, rocket.y, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(renderer, &rocketRect);
        }

        SDL_RenderPresent(renderer);
    }

    void run() {
        while (running) {
            handleEvents();
            update();
            render();
            SDL_Delay(SNAKE_SPEED);
        }
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    SnakeGame game;
    game.run();
    return 0;
}