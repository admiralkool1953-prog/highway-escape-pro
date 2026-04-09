# 🎮 Variantes et Extensions du Jeu

Ce document propose des idées pour améliorer et étendre **Highway Escape PRO**.

## 📦 Version Basique (Actuelle)

```
Caractéristiques:
✓ Controlé par flèches
✓ Obstacles aléatoires
✓ Système de santé (3 HP)
✓ Score (10 points par obstacle)
✓ Game Over
```

## 🚀 Variante 1: Jeu Réaliste

Ajouter des mécaniques plus RP réalistes:

```c
// Bonus à ajouter
- Carburant à gérer
- Vitesse variable (1-100 km/h)
- Cinture de sécurité (Protection bonus)
- Types de voitures ennemies différents
- Pluie/Brouillard (réduction visibilité)
```

**Fichiers à modifier:**
- [src/main.c](src/main.c) - Ajouter structures CarFuel, Weather
- [include/game.h](include/game.h) - Nouvelles structures

## 🎯 Variante 2: Jeu Multi-Niveaux

Ajouter une progression avec niveaux:

```c
Level 1: Vitesse base, obstacles lents
Level 2: Vitesse augmente, plus d'obstacles
Level 3: Chaos complet (tous les obstacles)

Système de points:
- Chaque level a un seuil de points
- Montée automatique du niveau
- Boss final sur level 3
```

## 🎨 Variante 3: Jeu Arcade

Style rétro des années 80:

```
- Pixels art (petit sprite 8x8)
- Écran plus petit (400x300)
- Police rétro
- Sons bips/bops
- Code couleurs vif (Néon)
```

## 🌟 Variante 4: Jeu Puzzle

Mode puzzle où vous devez:

```
- Éviter des obstacles en une séquence précise
- Collecter des bonus dans un ordre spécifique
- Niveaux pré-programmés (pré-calculés)
```

## 💪 Variante 5: Compétitif

Mode multiplayer local:

```c
// Deux joueurs:
- Joueur 1: Flèches directionnelles
- Joueur 2: WASD
- Écran partagé
- Chacun a sa santé
- Dernière voiture debout gagne
```

## 📱 Variante 6: Mobile (Web)

Compiler pour HTML5 avec Emscripten:

```bash
# Compiler pour Web
emcripten main.c -o game.html -lraylib

# Jouer dans navigateur
```

## 🎬 Extensions Recommandées

### Extension 1: Système de Sons

```c
// Ajouter dans main.c
#include "raylib.h"

void InitAudio(void) {
    InitAudioDevice();
    // Charger sons
}

void PlayCollisionSound(void) {
    PlaySound(collisionSound);
}
```

### Extension 2: Sauvegarde de Score

```c
// Sauvegarde dans fichier .txt
void SaveHighScore(int score, const char* name) {
    FILE *f = fopen("highscores.txt", "a");
    fprintf(f, "%s %d\n", name, score);
    fclose(f);
}
```

### Extension 3: Menu Principal

```c
// Écran de démarrage
typedef enum {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    HIGHSCORES
} GameState;

void DrawMenu(void) {
    DrawText("HIGHWAY ESCAPE PRO", 200, 150, 50, YELLOW);
    DrawText("Appuyez sur SPACE pour jouer", 200, 300, 20, WHITE);
}
```

### Extension 4: Niveaux de Difficulté

```c
typedef enum {
    EASY,      // 1.5s spawn, vitesse lente
    MEDIUM,    // 1.0s spawn, vitesse moyenne
    HARD,      // 0.7s spawn, vitesse rapide
    INSANE     // 0.5s spawn, vitesse très rapide
} Difficulty;

void SetDifficulty(Difficulty level) {
    switch(level) {
        case EASY:
            spawnRate = 1.5f;
            obstacleSpeed = 2.0f;
            break;
        // ... etc
    }
}
```

### Extension 5: Système de Puissance-ups

```c
typedef struct {
    Rectangle rect;
    int type;  // SHIELD, SPEED_BOOST, SLOW_TIME, MAGNET
    bool active;
} PowerUp;

void SpawnPowerUp(Game *game) {
    // Générateur aléatoire de puissance-ups
}

void ApplyPowerUp(Game *game, PowerUp *powerup) {
    switch(powerup->type) {
        case SHIELD:
            game->shieldActive = true;
            break;
        case SPEED_BOOST:
            game->speedMultiplier = 1.5f;
            break;
        // ... etc
    }
}
```

### Extension 6: Système de Particules

```c
typedef struct {
    Vector2 pos;
    Vector2 velocity;
    float lifetime;
    bool active;
} Particle;

void CreateExplosion(Vector2 pos, Game *game) {
    for (int i = 0; i < 10; i++) {
        // Créer particules
    }
}

void UpdateParticles(Game *game) {
    // Mettre à jour positions/lifetime
}
```

## 🎓 Ordre d'Apprentissage Recommandé

### Semaine 1: Bases
1. ✅ Version actuelle (Basique)
2. Ajouter Menu Principal
3. Ajouter Sons

### Semaine 2: Gameplay
4. Système Puissance-ups
5. Niveaux de Difficulté
6. Sauvegarde Scores

### Semaine 3: Avancé
7. Particules et Effets
8. Variante Multi-Joueur
9. Polish (UI/UX)

### Semaine 4: Déploiement
10. Optimisation Performance
11. Distribution (EXE)
12. Documentation

## 📊 Comparaison des Variantes

| Variante | Difficulté | Temps | Impact |
|----------|-----------|-------|--------|
| Réaliste | ⭐⭐ | 4h | Immersif |
| Multi-Niveaux | ⭐⭐ | 3h | Rejouabilité |
| Arcade | ⭐ | 2h | Nostalgie |
| Puzzle | ⭐⭐⭐ | 6h | Créatif |
| Compétitif | ⭐⭐⭐ | 5h | Fun |
| Mobile | ⭐⭐⭐⭐ | 8h | Portabilité |

## 🛠️ Modèle d'Extension

Voici un template pour ajouter une feature:

```c
// 1. Déclarer dans include/game.h
typedef struct {
    // Vos données
} NewFeature;

// 2. Initialiser dans src/main.c
void InitNewFeature(Game *game) {
    // Initialisation
}

// 3. Mettre à jour dans UpdateGame()
void UpdateNewFeature(Game *game) {
    // Logique
}

// 4. Afficher dans DrawGame()
void DrawNewFeature(Game *game) {
    // Rendu
}

// 5. Intégrer dans la boucle principale
int main(void) {
    // ...
    InitNewFeature(&game);
    
    while (!WindowShouldClose()) {
        UpdateNewFeature(&game);
        DrawNewFeature(&game);
    }
}
```

## 🔗 Ressources pour Extensions

### Sons
- `raylib` Audio: https://raylib.com/examples.html
- Freesound: https://freesound.org/

### Sprites/Graphics
- OpenGameArt: https://opengameart.org/
- Aseprite: https://www.aseprite.org/

### Music
- Incompetech: https://incompetech.com/
- OpenGameArt Music: https://opengameart.org/art-search?tags=music

## 🎯 Impact Potentiel

```
Basique (Actuelle)     → Prototype fonctionnel ✓
+ Menu               → Plus professionnel
+ Sons               → Plus immersif
+ Puissance-ups      → Plus varié
+ Niveaux            → Plus replayable
+ Particules         → Plus beau
+ Multijoueur        → Plus social
+ Mobile Web         → Plus accessible

= Jeu commercial viable!
```

---

**Choisissez une variante et commencez à développer! 🚀**

Suggestions:
1. Pour débuter: **Menu + Sons**
2. Pour l'immersion: **Variante Réaliste**
3. Pour le challenge: **Multi-Niveaux**
4. Pour la fun: **Multijoueur**
