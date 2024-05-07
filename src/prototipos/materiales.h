#ifndef MATERIALES_H
#define MATERIALES_H
#include "menu.h"
#include "materiales.h"

#define MAX_MOVES 28 // Número máximo de movimientos posibles en una jugada, como para la Reina

typedef struct {
  int x;
  int y;
} Move;

typedef struct {
  GdkPixbuf *imagen;
  char tipo;
  int color;
  int valor;
  int coordenadaX;
  int coordenadaY;
  int capturada;
} Pieza;

typedef struct {
  Pieza *casillas[8][8];
} Tablero;

typedef struct {
  Move posiblesMovimientos[MAX_MOVES]; // Definición en estructura
  int numMovimientos;                  // Definición en estructura
} AnalizadorMovimientos;

extern AnalizadorMovimientos analizador; // Variable externa

#endif