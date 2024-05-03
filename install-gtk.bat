@echo off
setlocal

:: Define la ruta donde se guardará el instalador, debe ser en la carpeta de documentos del usuario:

:: Usar la carpeta temporal del usuario
set INSTALLER_PATH=%TEMP%\msys2_installer.exe

:: Verificar si MSYS2 ya está instalado
where pacman >nul 2>nul
if %errorlevel% neq 0 (
    echo Instalando MSYS2...
    powershell -command "Invoke-WebRequest -Uri 'https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe' -OutFile '%INSTALLER_PATH%'"
    if not exist "%INSTALLER_PATH%" (
        echo Error: Fallo la descarga de MSYS2.
        exit /b 1
    )
    echo #DEBUG: %INSTALLER_PATH% descargado correctamente.
    cmd /c "%INSTALLER_PATH%"
    if %errorlevel% neq 0 (
        echo Error: Fallo la instalación de MSYS2.
        exit /b 1
    )
    set "PATH=%PATH%;C:\msys64\usr\bin;C:\msys64\mingw64\bin"
)

:: Actualizar MSYS2M
echo Actualizando MSYS2...
bash -lc "pacman -Syu --noconfirm"

:: Instalar GTK
echo Instalando GTK...
bash -lc "pacman -S mingw-w64-x86_64-gtk3 --noconfirm"

echo GTK instalado correctamente.
endlocal