#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

// Structures
typedef struct {
    Rectangle rect;
    Vector2 velocity;
    bool active;
} Car;

typedef struct {
    Car player;
    Car obstacles[10];
    int obstacleCount;
    int score;
    int health;
    float spawnTimer;
    bool gameOver;
} Game;

// Prototypes
void InitGame(Game *game);
void UpdateGame(Game *game);
void DrawGame(Game *game);
void CloseGame(Game *game);

#endif
