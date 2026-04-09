# 🎮 Highway Escape PRO - Résumé du Projet

## 📝 Qu'est-ce que c'est?

Un jeu vidéo 2D minimaliste en C avec Raylib où:
- ✅ Vous contrôlez une voiture bleue
- ✅ Des voitures rouges apparaissent aléatoirement
- ✅ Vous devez les éviter le plus longtemps possible
- ✅ Chaque obstacle évité vous rapporte 10 points
- ✅ Vous avez 3 points de santé
- ✅ Game Over quand votre santé = 0

## 🎯 Objectifs du Projet

### Concepts Implémentés
1. **Programmation en Temps Réel** - Boucle de jeu 60 FPS
2. **Gestion Graphique** - Raylib pour le rendu
3. **Physique Simple** - Collisions rectangulaires
4. **Génération Aléatoire** - Obstacles aléatoires
5. **Interface Utilisateur** - Score, santé, états du jeu

### Mécaniques du Jeu
| Élément | Description |
|---------|-------------|
| **Joueur** | Rectangle bleu contrôlable |
| **Obstacles** | Rectangles rouges tombants |
| **Collision** | Détection simple rectangle-rectangle |
| **Difficulty** | Vitesse croissante avec le temps |
| **Scoring** | +10 points par obstacle évité |
| **Health** | 3 points, -1 par collision |

## 📂 Structure du Projet

```
jeu voiture/
│
├── src/
│   └── main.c                 # Code principal complet
│
├── include/
│   └── game.h                 # En-têtes et structures
│
├── build/                     # Dossier compilé (généré)
│   ├── main.o
│   └── highway_escape.exe     # Exécutable final
│
├── .vscode/                   # Configuration VS Code
│   ├── c_cpp_properties.json  # Include paths
│   ├── launch.json            # Debug configuration
│   └── tasks.json             # Build tasks
│
├── CMakeLists.txt             # Configuration CMake
├── Makefile                   # Configuration Make
├── compile.bat                # Script batch Windows
├── compile.ps1                # Script PowerShell Windows
│
├── README.md                  # Documentation principale
├── INSTALLATION.md            # Guide installation Raylib
├── RAYLIB_CHECK.md            # Vérification Raylib
└── PROJECT_SUMMARY.md         # Ce fichier
```

## ⚙️ Dépendances Techniques

### Langage & Compilateur
- **Langage**: C (standard C99)
- **Compilateur**: GCC (MinGW sur Windows)
- **Chaîne de compilation**: Makefile, CMake, ou manuelle

### Bibliothèque Graphique
- **Raylib**: Bibliothèque graphique 2D
- **OpenGL**: Backend graphique
- **Dépendances**: 
  - `opengl32` (Windows)
  - `gdi32` (Windows)
  - `winmm` (Windows)

## 🚀 Démarrage Rapide

### 1. Installer Raylib
```bash
# Windows (Chocolatey)
choco install raylib mingw

# Ou via vcpkg
vcpkg install raylib:x64-windows
```

### 2. Compiler
```bash
# Méthode 1: Script Windows
compile.bat

# Méthode 2: Make
make

# Méthode 3: CMake
mkdir build && cd build && cmake .. && cmake --build .
```

### 3. Exécuter
```bash
build/highway_escape.exe
```

## 🎮 Commandes du Jeu

| Action | Touche |
|--------|--------|
| Aller à gauche | ← (Flèche gauche) |
| Aller à droite | → (Flèche droite) |
| Aller en avant | ↑ (Flèche haut) |
| Aller en arrière | ↓ (Flèche bas) |
| Recommencer | SPACE (après Game Over) |
| Quitter | ESC ou fermer la fenêtre |

## 📊 Système de Scoring

```
Score = Obstacles Évités × 10

Exemple:
- 5 obstacles évités = 50 points
- 10 obstacles évités = 100 points
- 25 obstacles évités = 250 points
```

## 💻 Code Principal

### Architecture Modulaire

```c
// game.h - Structures et déclarations
typedef struct {
    Rectangle rect;
    Vector2 velocity;
    bool active;
} Car;

// main.c - Implémentation
void InitGame(Game *game)      // Initialisation
void UpdateGame(Game *game)    // Logique à chaque frame
void DrawGame(Game *game)      // Rendu à chaque frame
void SpawnObstacle(Game *game) // Génération obstacles
```

### Boucle Principale
```c
while (!WindowShouldClose()) {
    UpdateGame(&game);  // Mise à jour logique
    DrawGame(&game);    // Affichage
}
```

## 🔧 Options de Compilation

### Windows MinGW
```bash
gcc -o highway_escape.exe src/main.c -Iinclude \
    -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Linux
```bash
gcc -o highway_escape src/main.c -Iinclude \
    $(pkg-config --cflags --libs raylib)
```

### macOS
```bash
gcc -o highway_escape src/main.c -Iinclude \
    -lraylib -framework CoreVideo -framework IOKit \
    -framework Cocoa -framework OpenGL
```

## 📈 Améliorations Possibles

### Courte Portée
- [ ] Son et musique de fond
- [ ] Particules sur collision
- [ ] Power-ups (bouclier, vitesse)
- [ ] Menu principal

### Moyenne Portée
- [ ] Niveaux de difficulté
- [ ] Meilleur système de scoring
- [ ] Classement persistant (highscores)
- [ ] Animations fluides

### Longue Portée
- [ ] Multijoueur local
- [ ] Cartes différentes
- [ ] Variétés d'obstacles
- [ ] Système de progression

## 🐛 Débogage

### En cas de problème

1. **Vérifier l'installation Raylib**
   ```bash
   # Windows
   gcc -c test.c -o test.o  # Si ça marche, c'est OK
   
   # Linux
   pkg-config --modversion raylib
   ```

2. **Consulter les logs de compilation**
   - Garder les messages d'erreur complets
   - Google l'erreur exacte

3. **Réinstaller Raylib**
   - Supprimer l'ancienne installation
   - Refaire l'installation complète

## 📚 Ressources d'Apprentissage

### Raylib
- [Raylib Official](https://raylib.com)
- [GitHub Raylib](https://github.com/raysan5/raylib)
- [Raylib Examples](https://github.com/raysan5/raylib/tree/master/examples)

### Programmation C
- [C Reference](https://en.cppreference.com/w/c)
- [Learn C](https://www.learn-c.org/)

### Gamedev
- [Game Development Basics](https://www.youtube.com/results?search_query=raylib+game+tutorial)

## ✅ Listes de Vérification

### Installation Raylib
- [ ] GCC/MinGW installé
- [ ] Raylib framework installé
- [ ] Variables d'environnement configurées
- [ ] Compilation de test réussie

### Compilation du Jeu
- [ ] `src/main.c` présent
- [ ] `include/game.h` présent
- [ ] Dossier `build/` créé
- [ ] Exécutable généré sans erreurs

### Exécution du Jeu
- [ ] Fenêtre s'ouvre
- [ ] Voiture bleue visible
- [ ] Obstacles rouges apparaissent
- [ ] Collisions fonctionnent
- [ ] Score s'incrémente

## 📞 Support

En cas de problème:
1. Consulter [INSTALLATION.md](INSTALLATION.md)
2. Consulter [RAYLIB_CHECK.md](RAYLIB_CHECK.md)
3. Lire [README.md](README.md)
4. Chercher sur GitHub: https://github.com/raysan5/raylib/issues

---

**Créé avec ❤️ pour l'apprentissage du C et des jeux vidéo 2D**

*Highway Escape PRO - Mini-projet 2D en C avec Raylib*
