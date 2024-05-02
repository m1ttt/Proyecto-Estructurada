@echo off
setlocal

:: Verificar si MSYS2 ya está instalado
where pacman >nul 2>nul
if %errorlevel% neq 0 (
    echo Instalando MSYS2...
    powershell -command "Invoke-WebRequest -Uri 'https://github.com/msys2/msys2-installer/releases/download/2022-05-24/msys2-x86_64-20220524.exe' -OutFile 'msys2-installer.exe'"
    start /wait msys2-installer.exe
    set "PATH=%PATH%;C:\msys64\usr\bin;C:\msys64\mingw64\bin"
)

:: Actualizar MSYS2
echo Actualizando MSYS2...
bash -lc "pacman -Syu --noconfirm"

:: Instalar GTK
echo Instalando GTK...
bash -lc "pacman -S mingw-w64-x86_64-gtk3 --noconfirm"

echo GTK instalado correctamente.
endlocal
