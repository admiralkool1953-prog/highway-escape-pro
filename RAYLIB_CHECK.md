# Vérification de l'installation de Raylib

## Qu'est-ce que Raylib?

Raylib est une bibliothèque graphique multiplateforme simple et facile à utiliser pour créer des jeux vidéo et des applications graphiques en C.

## Vérifications rapides

### Windows

#### Option 1: Invite de commande
```bash
# Vérifier si gcc est installé
gcc --version

# Essayer une compilation simple
gcc -c test.c -o test.o
del test.o test.c
```

#### Option 2: PowerShell
```powershell
# Vérifier gcc
Get-Command gcc

# Lancer le script de vérification
powershell -ExecutionPolicy Bypass -File compile.ps1
```

### Linux

```bash
# Vérifier l'installation
pkg-config --modversion raylib

# Alternativement
ldconfig -p | grep raylib
```

### macOS

```bash
# Via Homebrew
brew list raylib

# Ou vérifier le framework
ls -la /usr/local/include/raylib.h
```

## Installation complète de Raylib

### Windows avec MinGW

#### Étape 1: Installer MinGW
1. Télécharger depuis: https://www.mingw-w64.org/
2. Exécuter l'installateur
3. Sélectionner les options par défaut
4. Ajouter `/mingw64/bin` au PATH

#### Étape 2: Installer Raylib

**Méthode A: Via vcpkg (Recommandé)**
```bash
# Installer vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Installer raylib
.\vcpkg install raylib:x64-windows
```

**Méthode B: Compilation manuelle**
```bash
# Cloner le repo
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Compiler avec MinGW
gcc -O2 *.c -c -Wall -Wextra -fPIC
ar rcs libraylib.a *.o

# Copier les fichiers
copy raylib.h C:\MinGW\include\
copy libraylib.a C:\MinGW\lib\
```

### Linux (Ubuntu/Debian)

```bash
# Installation simple
sudo apt-get update
sudo apt-get install libraylib-dev build-essential

# Vérifier
pkg-config --cflags --libs raylib
```

### Linux (Fedora)

```bash
sudo dnf install raylib-devel gcc

# Vérifier
pkg-config --modversion raylib
```

### macOS

```bash
# Via Homebrew
brew install raylib

# Via source
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
sudo make install
```

## Diagnostic d'erreurs courantes

### Erreur: "raylib.h: No such file or directory"

**Causes possibles:**
1. Raylib n'est pas installé
2. Le compilateur ne trouve pas les fichiers include
3. Le PATH n'est pas configuré

**Solutions:**
```bash
# Vérifier la localisation
find / -name "raylib.h" 2>/dev/null

# Avec chemin explicite
gcc -I/chemin/vers/raylib/include -c mon_fichier.c
```

### Erreur: "undefined reference to 'InitWindow'"

**Cause:** Les bibliothèques Raylib ne sont pas liées

**Solution:**
```bash
# Ajouter les flags de liaison
gcc -o mon_exe mon_fichier.c -lraylib -lopengl32 -lgdi32 -lwinmm  # Windows
gcc -o mon_exe mon_fichier.c $(pkg-config --libs raylib)        # Linux
```

### Erreur: "cannot find -lraylib"

**Cause:** Le compilateur ne trouve pas libraylib

**Solutions:**
```bash
# Vérifier l'installation
ldconfig -p | grep raylib    # Linux
ls -la /usr/lib/*raylib*      # Linux

# Avec chemin complet
gcc -L/chemin/vers/raylib/lib -lraylib ...
```

## Vérification post-installation

Créez ce fichier `test_raylib.c`:

```c
#include "raylib.h"
#include <stdio.h>

int main(void) {
    printf("Raylib version OK\n");
    return 0;
}
```

Compilez:

```bash
# Windows (MinGW)
gcc test_raylib.c -o test_raylib -lraylib -lopengl32 -lgdi32 -lwinmm

# Linux
gcc test_raylib.c -o test_raylib $(pkg-config --cflags --libs raylib)

# macOS
gcc test_raylib.c -o test_raylib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL

# Exécutez
./test_raylib
```

Un affichage confirmant l'installation = ✓ Raylib est installé


## Ressources

- **Site officiel:** https://www.raylib.com/
- **GitHub:** https://github.com/raysan5/raylib
- **Documentation:** https://github.com/raysan5/raylib/wiki
- **Exemples:** https://github.com/raysan5/raylib/tree/master/examples

## Support

Pour des problèmes:
1. Vérifier les logs de compilation
2. Consulter https://github.com/raysan5/raylib/issues
3. Essayer une réinstallation complète
