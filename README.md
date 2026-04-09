# Highway Escape PRO - Jeu C avec Raylib

Un jeu vidéo 2D défis d'évitement de voitures sur une autoroute, développé en C avec la bibliothèque Raylib.

## Caractéristiques

- 🎮 Contrôle fluide d'une voiture avec les flèches du clavier
- 🚗 Obstacles (voitures ennemies) générés aléatoirement
- 💥 Système de collision détectable
- 📊 Système de score et d'état de santé
- 🎯 Gameplay infini jusqu'à la fin de la partie

## Contrôles

- **Flèches Haut/Bas**: Avancer/Reculer
- **Flèches Gauche/Droite**: Tourner
- **SPACE**: Recommencer après Game Over

## Prérequis

### Windows avec MinGW/GCC

1. **Installer GCC (MinGW)**
   - Télécharger depuis: https://www.mingw-w64.org/
   - Ajouter à PATH

2. **Installer Raylib**
   ```bash
   # Option 1: Via vcpkg
   vcpkg install raylib:x64-windows
   
   # Option 2: Compilation manuelle
   # Cloner depuis https://github.com/raysan5/raylib
   # Suivre les instructions dans le README
   ```

3. **Installer Make (optionnel)**
   ```bash
   choco install make  # via Chocolatey
   ```

### Windows avec MSVC

1. **Installer Visual Studio Community**
2. **Installer Raylib**
   ```bash
   vcpkg install raylib:x64-windows-static-md
   ```

### Linux

```bash
# Ubuntu/Debian
sudo apt-get install build-essential libraylib-dev

# Fedora
sudo dnf install gcc raylib-devel

# Arch
sudo pacman -S raylib
```

### macOS

```bash
brew install raylib
```

## Compilation

### Option 1: Avec Make
```bash
make
make run
```

### Option 2: Avec CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
./highway_escape  # ou highway_escape.exe sous Windows
```

### Option 3: Compilation manuelle
```bash
# Windows (MinGW)
gcc -o build/highway_escape.exe src/main.c -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm

# Linux
gcc -o build/highway_escape src/main.c -Iinclude $(pkg-config --cflags --libs raylib)

# macOS
gcc -o build/highway_escape src/main.c -Iinclude -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
```

## Vérifier l'installation de Raylib

### Windows (MinGW)
```bash
# Test rapide
gcc --version
# Vérifier que Raylib est dans le PATH
gcc -c test.c -Ipath/to/raylib/include
```

### Linux
```bash
pkg-config --modversion raylib
```

### macOS
```bash
brew list raylib
```

## Structure du Projet

```
jeu voiture/
├── src/
│   └── main.c              # Logique principale du jeu
├── include/
│   └── game.h              # En-têtes et structures
├── build/                  # Dossier de sortie compilé
├── Makefile                # Configuration Make
├── CMakeLists.txt          # Configuration CMake
└── README.md               # Ce fichier
```

## Gameplay

1. **Objectif**: Éviter les voitures rouges aussi longtemps que possible
2. **Santé**: Vous commencez avec 3 points de santé
3. **Score**: +10 points pour chaque obstacle évité
4. **Game Over**: Quand la santé atteint 0

## Problèmes Courants

### "raylib.h: No such file or directory"
- Raylib n'est pas installé ou pas trouvé
- Vérifier le PATH des compilateurs
- Essayer une installation manuelle

### Erreur de liaison (linking error)
- S'assurer que les bibliothèques Raylib sont liées
- Vérifier le dossier lib/ de Raylib

### L'exécutable ne se lance pas sous Windows
- S'assurer que raylib.dll est dans le PATH
- Copier raylib.dll dans le même dossier que l'exécutable

## Améliorations Futures

- [ ] Niveaux de difficulté
- [ ] Puissance-ups (bouclier, vitesse, etc.)
- [ ] Sons et musique
- [ ] Meilleur système de scoring
- [ ] Menus et paramètres
- [ ] Particules et effets visuels

## Licence

CC0 1.0 - Domaine Public

## Auteur

Développé en C avec ❤️ et Raylib
