#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"

void InitGame(Game *game) {
    // Initialiser la voiture du joueur
    game->player.rect = (Rectangle){(SCREEN_WIDTH / 2) - 20, SCREEN_HEIGHT - 80, 40, 60};
    game->player.velocity = (Vector2){0, 0};
    game->player.active = true;
    
    // Initialiser les variables de jeu
    game->obstacleCount = 0;
    game->score = 0;
    game->health = 3;
    game->spawnTimer = 0;
    game->gameOver = false;
    
    // Initialiser les obstacles
    for (int i = 0; i < 10; i++) {
        game->obstacles[i].active = false;
    }
}

void SpawnObstacle(Game *game) {
    for (int i = 0; i < 10; i++) {
        if (!game->obstacles[i].active) {
            int lane = GetRandomValue(0, 2) * 130 + 50;
            game->obstacles[i].rect = (Rectangle){lane, -60, 40, 60};
            game->obstacles[i].velocity = (Vector2){0, GetRandomValue(3, 5)};
            game->obstacles[i].active = true;
            game->obstacleCount++;
            break;
        }
    }
}

void UpdateGame(Game *game) {
    if (game->gameOver) {
        if (IsKeyPressed(KEY_SPACE)) {
            InitGame(game);
            SetWindowTitle("Highway Escape PRO - Restarting...");
        }
        return;
    }
    
    // Contrôles du joueur
    if (IsKeyDown(KEY_LEFT) && game->player.rect.x > 0) {
        game->player.rect.x -= 5;
    }
    if (IsKeyDown(KEY_RIGHT) && game->player.rect.x + game->player.rect.width < SCREEN_WIDTH) {
        game->player.rect.x += 5;
    }
    if (IsKeyDown(KEY_UP) && game->player.rect.y > 100) {
        game->player.rect.y -= 3;
    }
    if (IsKeyDown(KEY_DOWN) && game->player.rect.y + game->player.rect.height < SCREEN_HEIGHT) {
        game->player.rect.y += 3;
    }
    
    // Gestion des obstacles
    game->spawnTimer += GetFrameTime();
    if (game->spawnTimer >= 1.5f) {
        SpawnObstacle(game);
        game->spawnTimer = 0;
    }
    
    // Mise à jour des obstacles
    for (int i = 0; i < 10; i++) {
        if (game->obstacles[i].active) {
            game->obstacles[i].rect.y += game->obstacles[i].velocity.y;
            
            // Vérifier les collisions
            if (CheckCollisionRecs(game->player.rect, game->obstacles[i].rect)) {
                game->health--;
                game->obstacles[i].active = false;
                game->obstacleCount--;
                
                if (game->health <= 0) {
                    game->gameOver = true;
                }
            }
            
            // Supprimer si hors écran
            if (game->obstacles[i].rect.y > SCREEN_HEIGHT) {
                game->obstacles[i].active = false;
                game->obstacleCount--;
                game->score += 10;
            }
        }
    }
}

void DrawGame(Game *game) {
    BeginDrawing();
    
    ClearBackground(DARKGRAY);
    
    // Dessiner la route
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){64, 64, 64, 255});
    
    // Dessiner les lignes de la route
    for (int i = 0; i < SCREEN_HEIGHT; i += 30) {
        DrawRectangle(SCREEN_WIDTH/2 - 2, i, 4, 20, YELLOW);
    }
    
    // Dessiner les bordures
    DrawRectangle(0, 0, 50, SCREEN_HEIGHT, (Color){100, 100, 100, 255});
    DrawRectangle(SCREEN_WIDTH - 50, 0, 50, SCREEN_HEIGHT, (Color){100, 100, 100, 255});
    
    // Dessiner le joueur
    DrawRectangleRec(game->player.rect, BLUE);
    DrawRectangleLines((int)game->player.rect.x, (int)game->player.rect.y, 
                       (int)game->player.rect.width, (int)game->player.rect.height, WHITE);
    
    // Dessiner les obstacles
    for (int i = 0; i < 10; i++) {
        if (game->obstacles[i].active) {
            DrawRectangleRec(game->obstacles[i].rect, RED);
            DrawRectangleLines((int)game->obstacles[i].rect.x, (int)game->obstacles[i].rect.y,
                             (int)game->obstacles[i].rect.width, (int)game->obstacles[i].rect.height, MAROON);
        }
    }
    
    // Interface utilisateur
    DrawText(TextFormat("Score: %d", game->score), 20, 20, 20, WHITE);
    DrawText(TextFormat("Sante: %d", game->health), 20, 50, 20, WHITE);
    DrawText(TextFormat("Obstacles: %d", game->obstacleCount), 20, 80, 20, WHITE);
    
    // Écran de game over
    if (game->gameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 128});
        DrawText("GAME OVER", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 60, 60, RED);
        DrawText(TextFormat("Score Final: %d", game->score), SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 40, 30, WHITE);
        DrawText("Appuyez sur SPACE pour recommencer", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 + 100, 20, YELLOW);
    }
    
    EndDrawing();
}

void CloseGame(Game *game) {
    CloseWindow();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Highway Escape PRO");
    SetTargetFPS(FPS);
    
    srand((unsigned int)time(NULL));
    
    Game game = {0};
    InitGame(&game);
    
    while (!WindowShouldClose()) {
        UpdateGame(&game);
        DrawGame(&game);
    }
    
    CloseGame(&game);
    
    return 0;
}
