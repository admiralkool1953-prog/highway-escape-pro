# Installation & Déploiement de Raylib

## ✅ Vérification Rapide d'Installation

Exécutez l'un de ces scripts:

### Sous Windows (Batch)
```bash
compile.bat
```

### Sous Windows (PowerShell)
```powershell
powershell -ExecutionPolicy Bypass -File compile.ps1
```

### Sous Linux/macOS
```bash
make
make run
```

---

## 📋 Étapes d'Installation (Windows)

### 1️⃣ Installer MinGW (Compilateur C)

```bash
# Via Chocolatey (recommandé)
choco install mingw

# Ou télécharger: https://www.mingw-w64.org/

# Vérifier l'installation
gcc --version
```

### 2️⃣ Installer Raylib

#### Option A: Via vcpkg (Recommandé - Le plus simple)

```bash
# Installer vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Installer raylib
.\vcpkg install raylib:x64-windows

# Intégrer avec CMake (optionnel)
.\vcpkg integrate install
```

#### Option B: Via Chocolatey

```bash
choco install raylib
```

#### Option C: Téléchargement Manuel

1. Aller à https://github.com/raysan5/raylib/releases
2. Télécharger la version Windows
3. Extraire dans `C:\raylib\` (par exemple)
4. Compiler ou utiliser les binaires précompilés

---

## 📋 Étapes d'Installation (Linux)

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libraylib-dev build-essential make cmake

# Vérifier
pkg-config --modversion raylib
```

### Fedora
```bash
sudo dnf install raylib-devel gcc make cmake

# Vérifier
pkg-config --modversion raylib
```

### Arch Linux
```bash
sudo pacman -S raylib

# Vérifier
pkg-config --modversion raylib
```

---

## 📋 Étapes d'Installation (macOS)

### Via Homebrew (Recommandé)
```bash
brew install raylib

# Vérifier
pkg-config --modversion raylib
```

### Via Source
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
sudo make install

# Vérifier
ls /usr/local/lib/libraylib.a
```

---

## 🔧 Compilation du Jeu

### Méthode 1: Make
```bash
make        # Compile le projet
make run    # Compile et exécute
make clean  # Nettoie les fichiers objets
```

### Méthode 2: CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
./highway_escape
```

### Méthode 3: Compilation manuelle

**Windows:**
```bash
gcc -o highway_escape.exe src/main.c -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm
```

**Linux:**
```bash
gcc -o highway_escape src/main.c -Iinclude $(pkg-config --cflags --libs raylib)
```

**macOS:**
```bash
gcc -o highway_escape src/main.c -Iinclude -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
```

---

## 🐛 Dépannage

### ❌ "gcc: command not found"
- GCC n'est pas installé
- Installer MinGW/GCC via Chocolatey ou les instructions ci-dessus

### ❌ "raylib.h: No such file or directory"
- Raylib n'est pas dans le PATH include
- Solutions:
  ```bash
  # Compiler avec chemin explicite
  gcc -I/chemin/vers/raylib/include ...
  
  # Ou configurer les variables d'environnement
  set RAYLIB_INCLUDE=C:\raylib\include
  set RAYLIB_LIB=C:\raylib\lib
  ```

### ❌ "undefined reference to 'InitWindow'"
- Les bibliothèques Raylib ne sont pas liées
- Ajouter les flags de compilation corrects:
  ```bash
  # Windows
  -lraylib -lopengl32 -lgdi32 -lwinmm
  
  # Linux
  $(pkg-config --libs raylib)
  
  # macOS
  -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
  ```

### ❌ "cannot find -lraylib"
```bash
# Vérifier le chemin des bibliothèques
gcc -L/chemin/vers/raylib/lib -o ... -lraylib ...

# Sur Windows, s'assurer que le .dll est dans le PATH
set PATH=%PATH%;C:\raylib\lib
```

---

## 📦 Distribution du Jeu

### Pour partager l'exécutable Windows

1. Créer un dossier `HighwayEscapePRO`
2. Copier `build/highway_escape.exe`
3. Copier les DLL nécessaires:
   ```bash
   raylib.dll
   opengl32.dll
   ```
4. Créer un raccourci pour lancer le jeu

### Pour partager le code source

1. Envoyer tous les fichiers:
   - `src/`
   - `include/`
   - `CMakeLists.txt` ou `Makefile`
   - `README.md`

2. Destinataire installe Raylib et compile localement

---

## ✔️ Vérification Finale

Exécutez ce test:

```c
// test.c
#include "raylib.h"
#include <stdio.h>

int main(void) {
    InitWindow(800, 600, "Test Raylib");
    printf("Raylib fonctionne!\n");
    CloseWindow();
    return 0;
}
```

Compilez et exécutez:
```bash
gcc test.c -o test -lraylib -lopengl32 -lgdi32 -lwinmm
./test
```

Si une fenêtre s'ouvre: ✅ **Raylib est correctement installé!**

---

## 📚 Ressources Utiles

- [Raylib Official](https://www.raylib.com/)
- [GitHub Raylib](https://github.com/raysan5/raylib)
- [Raylib Wiki](https://github.com/raysan5/raylib/wiki)
- [Raylib Examples](https://github.com/raysan5/raylib/tree/master/examples)
- [C Language Guide](https://www.cplusplus.com/reference/cstdio/)

---

**🎮 Bon jeu!**
