# Script pour télécharger et installer Raylib
param([switch]$Install)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Installation de Raylib pour Windows" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Créer le dossier
if (-not (Test-Path 'C:\raylib')) {
    New-Item -ItemType Directory -Path 'C:\raylib' -Force | Out-Null
    Write-Host "[+] Dossier C:\raylib créé" -ForegroundColor Green
}

# Télécharger Raylib
Write-Host "[*] Téléchargement de Raylib 4.5.0..." -ForegroundColor Yellow
$url = 'https://github.com/raysan5/raylib/releases/download/4.5.0/raylib-4.5.0_win64_mingw.zip'
$output = 'C:\raylib\raylib.zip'

try {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    
    $client = New-Object System.Net.WebClient
    $client.DownloadFile($url, $output)
    
    Write-Host "[OK] Raylib téléchargé avec succès" -ForegroundColor Green
    
    # Extraire
    Write-Host "[*] Extraction de l'archive..." -ForegroundColor Yellow
    Expand-Archive -Path $output -DestinationPath 'C:\raylib' -Force
    Write-Host "[OK] Archive extraite" -ForegroundColor Green
    
    # Ajouter au PATH
    Write-Host "[*] Configuration du PATH..." -ForegroundColor Yellow
    $raylib_bin = 'C:\raylib\raylib\bin'
    $raylib_lib = 'C:\raylib\raylib\lib'
    
    if (Test-Path $raylib_bin) {
        Write-Host "[OK] Raylib est prêt!" -ForegroundColor Green
        Write-Host "Include path: C:\raylib\raylib\include" -ForegroundColor Cyan
        Write-Host "Library path: $raylib_lib" -ForegroundColor Cyan
    }
    
} catch {
    Write-Host "[ERROR] Erreur de téléchargement: $_" -ForegroundColor Red
    Write-Host ""
    Write-Host "Alternatives:" -ForegroundColor Yellow
    Write-Host "1. Télécharger manuellement: https://github.com/raysan5/raylib/releases" -ForegroundColor White
    Write-Host "2. Installer MinGW via: https://www.mingw-w64.org/" -ForegroundColor White
    Write-Host "3. Utiliser WSL (Windows Subsystem for Linux)" -ForegroundColor White
}

Write-Host ""
Write-Host "Pour tester:" -ForegroundColor Cyan
Write-Host "gcc -I C:\raylib\raylib\include -L C:\raylib\raylib\lib -o test.exe main.c -lraylib -lopengl32 -lgdi32 -lwinmm" -ForegroundColor White
