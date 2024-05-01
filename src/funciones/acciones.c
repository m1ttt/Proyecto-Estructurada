#include "../prototipos/materiales.h"
#include <stdio.h>

void detectorDeSistema() {
#ifdef _WIN32
  printf("Windows\n");
#elif __APPLE__
  printf("Mac OS\n");
#elif __linux__
  printf("Linux\n");
#elif __unix__
  printf("Unix\n");
#else
  printf("Unknown\n");
#endif
}

void inicializarTablero(Tablero *tablero) {}

void imprimirTablero(Tablero *tablero) {}

void moverPieza(Tablero *tablero, int x1, int x2, int y1, int y2) {}
