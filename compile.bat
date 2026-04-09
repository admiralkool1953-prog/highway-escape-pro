@echo off
REM Script de compilation pour Highway Escape PRO
REM Compile le projet et lance le jeu

echo ========================================
echo Highway Escape PRO - Compilation
echo ========================================
echo.

REM Vérifier si gcc est installé
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERREUR: gcc n'est pas trouvé dans le PATH
    echo Veuillez installer MinGW/GCC
    pause
    exit /b 1
)

echo [1/3] Vérification de raylib...
REM Essayer une compilation simple pour vérifier raylib
echo #include "raylib.h" > test_raylib.c
echo int main() { return 0; } >> test_raylib.c
gcc -c test_raylib.c -o test_raylib.o 2>nul
if %errorlevel% neq 0 (
    echo AVERTISSEMENT: raylib peut ne pas être installé
    echo Essai de compilation malgré tout...
) else (
    echo [OK] raylib trouvé
)
del test_raylib.c test_raylib.o 2>nul

echo [2/3] Création du dossier build...
if not exist build (
    mkdir build
)

echo [3/3] Compilation du projet...
gcc -o build/highway_escape.exe src/main.c -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo Compilation réussie!
    echo ========================================
    echo.
    echo Lancer le jeu? (O/N)
    set /p choice=
    
    if /i "%choice%"=="O" (
        cd build
        highway_escape.exe
        cd ..
    ) else (
        echo Exécutable créé: build/highway_escape.exe
    )
) else (
    echo.
    echo ========================================
    echo ERREUR: La compilation a échoué
    echo ========================================
    echo.
    echo Assurez-vous que:
    echo 1. GCC est installé et dans le PATH
    echo 2. Raylib est correctement installé
    echo 3. Les bibliothèques graphiques sont disponibles
    pause
    exit /b 1
)
