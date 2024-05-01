#ifndef MATERIALES_H
#define MATERIALES_H

// Definicion de materiales del ajedrez.
typedef struct {
  char tipo; // KING, QUEEN, TORRE, ALFIL, CABALLO, PEON. (K, Q, T, A, C, P)
  int color; // BLANCO O NEGRO
} Pieza;

typedef struct {
  Pieza *pieza;
} Casilla;

typedef struct {
  Casilla casillas[8][8];
} Tablero;

#endif
