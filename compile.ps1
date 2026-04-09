# Script de compilation et vérification pour Highway Escape PRO
# Usage: powershell -ExecutionPolicy Bypass -File compile.ps1

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Highway Escape PRO - Système de Compilation" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Vérifier GCC
Write-Host "[*] Vérification de GCC..." -ForegroundColor Yellow
try {
    $gcc = Get-Command gcc -ErrorAction Stop
    Write-Host "[OK] GCC trouvé: $($gcc.Source)" -ForegroundColor Green
    gcc --version | Select-Object -First 1
} catch {
    Write-Host "[ERROR] GCC n'est pas installé" -ForegroundColor Red
    Write-Host "Installez MinGW depuis https://www.mingw-w64.org/" -ForegroundColor Yellow
    exit 1
}

# Vérifier Raylib
Write-Host ""
Write-Host "[*] Vérification de Raylib..." -ForegroundColor Yellow

$testFile = "test_raylib.c"
$testObj = "test_raylib.o"

@"
#include "raylib.h"
int main() { return 0; }
"@ | Out-File -FilePath $testFile -Encoding ASCII

if (gcc -c $testFile -o $testObj 2>&1) {
    Write-Host "[OK] Raylib est accessible" -ForegroundColor Green
    Remove-Item $testFile, $testObj -Force 2>$null
} else {
    Write-Host "[WARNING] Raylib peut ne pas être correctement installé" -ForegroundColor Yellow
    Remove-Item $testFile -Force 2>$null
    Write-Host ""
    Write-Host "Instructions pour installer Raylib:" -ForegroundColor Cyan
    Write-Host "1. Télécharger: https://github.com/raysan5/raylib/releases" -ForegroundColor White
    Write-Host "2. Extraire et compiler" -ForegroundColor White
    Write-Host "3. Ajouter à PATH: C:\path\to\raylib\lib" -ForegroundColor White
}

# Créer le dossier build
Write-Host ""
Write-Host "[*] Préparation du dossier build..." -ForegroundColor Yellow
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" -Force | Out-Null
    Write-Host "[OK] Dossier build créé" -ForegroundColor Green
} else {
    Write-Host "[OK] Dossier build existe déjà" -ForegroundColor Green
}

# Compiler
Write-Host ""
Write-Host "[*] Compilation du projet..." -ForegroundColor Yellow
$compileCmd = "gcc -o build/highway_escape.exe src/main.c -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm"

if (Invoke-Expression $compileCmd 2>$null) {
    Write-Host "[OK] Compilation réussie!" -ForegroundColor Green
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Exécutable généré: build/highway_escape.exe" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Cyan
    
    $run = Read-Host -Prompt "Lancer le jeu maintenant? (o/n)"
    if ($run -eq "o" -or $run -eq "O") {
        Write-Host ""
        Write-Host "Lancement du jeu..." -ForegroundColor Yellow
        & ".\build\highway_escape.exe"
    }
} else {
    Write-Host "[ERROR] La compilation a échoué" -ForegroundColor Red
    Write-Host ""
    Write-Host "Assurez-vous que:" -ForegroundColor Yellow
    Write-Host "1. GCC est correctement installé" -ForegroundColor White
    Write-Host "2. Raylib est correctement installé" -ForegroundColor White
    Write-Host "3. Les variables d'environnement sont configurées" -ForegroundColor White
    exit 1
}
