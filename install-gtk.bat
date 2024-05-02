#!/bin/bash

# Instalar MSYS2
curl -LO "https://github.com/msys2/msys2-installer/releases/download/2021-02-28/msys2-x86_64-20210228.exe"
./msys2-x86_64-20210228.exe

# Iniciar MSYS2 y actualizar
msys2_shell.cmd -mingw64 -c "pacman -Syu"

# Instalar GTK
msys2_shell.cmd -mingw64 -c "pacman -S mingw-w64-x86_64-gtk3"
