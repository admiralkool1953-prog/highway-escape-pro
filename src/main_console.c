#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PLAYER_POS_Y (SCREEN_HEIGHT - 3)

typedef struct {
    int x;
    int y;
    int active;
} Obstacle;

typedef struct {
    int x;
    int score;
    int health;
    Obstacle obstacles[10];
    int obstacleCount;
    int gameOver;
    int level;
} Game;

void ClearScreen() {
    system("cls");
}

void InitGame(Game *game) {
    game->x = SCREEN_WIDTH / 2;
    game->score = 0;
    game->health = 3;
    game->obstacleCount = 0;
    game->gameOver = 0;
    game->level = 1;
    
    for (int i = 0; i < 10; i++) {
        game->obstacles[i].active = 0;
    }
}

void SpawnObstacle(Game *game) {
    for (int i = 0; i < 10; i++) {
        if (!game->obstacles[i].active) {
            game->obstacles[i].x = rand() % (SCREEN_WIDTH - 2);
            game->obstacles[i].y = 0;
            game->obstacles[i].active = 1;
            game->obstacleCount++;
            break;
        }
    }
}

void UpdateGame(Game *game) {
    if (game->gameOver) return;
    
    static int spawnCounter = 0;
    if (++spawnCounter > (20 - game->level * 2)) {
        SpawnObstacle(game);
        spawnCounter = 0;
    }
    
    // Update obstacles
    for (int i = 0; i < 10; i++) {
        if (game->obstacles[i].active) {
            game->obstacles[i].y++;
            
            // Check collision
            if (game->obstacles[i].y == PLAYER_POS_Y &&
                game->obstacles[i].x >= game->x - 1 && 
                game->obstacles[i].x <= game->x + 1) {
                game->health--;
                game->obstacles[i].active = 0;
                game->obstacleCount--;
                
                if (game->health <= 0) {
                    game->gameOver = 1;
                }
            }
            
            // Remove if off screen
            if (game->obstacles[i].y >= SCREEN_HEIGHT) {
                game->obstacles[i].active = 0;
                game->obstacleCount--;
                game->score += 10 * game->level;
                
                // Level up every 5 obstacles
                if (game->score % 50 == 0 && game->score > 0) {
                    game->level++;
                }
            }
        }
    }
}

void DrawGame(Game *game) {
    ClearScreen();
    
    // Draw header
    printf("══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("║ HIGHWAY ESCAPE PRO │ Score: %-8d │ Health: %-3d │ Level: %-2d │ Obstacles: %-3d            ║\n", 
           game->score, game->health, game->level, game->obstacleCount);
    printf("══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    
    // Draw game field
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        printf("║ ");
        
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int printed = 0;
            
            // Draw player
            if (y == PLAYER_POS_Y && x >= game->x - 1 && x <= game->x + 1) {
                printf("█");
                printed = 1;
            }
            
            // Draw obstacles
            if (!printed) {
                for (int i = 0; i < 10; i++) {
                    if (game->obstacles[i].active && 
                        game->obstacles[i].y == y && 
                        game->obstacles[i].x == x) {
                        printf("◆");
                        printed = 1;
                        break;
                    }
                }
            }
            
            // Draw road markings
            if (!printed) {
                if (x == SCREEN_WIDTH / 2) {
                    printf("·");
                } else if (x % 10 == 0) {
                    printf("│");
                } else {
                    printf(" ");
                }
            }
        }
        printf(" ║\n");
    }
    
    printf("══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("║ Controls: [A] Left  [D] Right  [Q] Quit                                                            ║\n");
    printf("══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    
    if (game->gameOver) {
        printf("\n");
        printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                      *** GAME OVER ***                                          ║\n");
        printf("║                                  Final Score: %-8d                                        ║\n", game->score);
        printf("║                                   Level Reached: %-2d                                         ║\n", game->level);
        printf("║                                                                                                 ║\n");
        printf("║                                   Press SPACE to restart                                       ║\n");
        printf("║                                    or Q to quit                                                ║\n");
        printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    
    Game game;
    InitGame(&game);
    
    printf("\n╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        WELCOME TO HIGHWAY ESCAPE PRO                                          ║\n");
    printf("║                                                                                               ║\n");
    printf("║  Avoid the obstacles (◆) coming your way! Use A/D to move left/right.                        ║\n");
    printf("║  Survive as long as possible and earn the highest score!                                     ║\n");
    printf("║                                                                                               ║\n");
    printf("║                              Press ENTER to start...                                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    getchar();
    
    while (1) {
        if (!game.gameOver) {
            UpdateGame(&game);
        }
        
        DrawGame(&game);
        
        // Input handling
        if (_kbhit()) {
            char input = _getch();
            input = tolower(input);
            
            if (input == 'a' && game.x > 1) {
                game.x--;
            } else if (input == 'd' && game.x < SCREEN_WIDTH - 2) {
                game.x++;
            } else if (input == 'q') {
                break;
            } else if (input == ' ' && game.gameOver) {
                InitGame(&game);
            }
        }
        
        // Game speed based on level
        Sleep(150 / game.level);
    }
    
    printf("\nThanks for playing Highway Escape PRO!\n");
    return 0;
}
