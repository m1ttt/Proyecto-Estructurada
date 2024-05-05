#ifndef MATERIALES_H
#define MATERIALES_H
#include <gtk-3.0/gtk/gtk.h>


#define MAX_MOVES                                                              \
  28 // Número máximo de movimientos posibles en una jugada, como para la Reina

typedef struct {
  int x;
  int y;
} Move;

typedef struct {
  GdkPixbuf *imagen;
  char tipo;
  int color;
  int coordenadaX;
  int coordenadaY;
  int capturada;
} Pieza;


typedef struct {
  Pieza *casillas[8][8];
} Tablero;

extern Move posiblesMovimientos[MAX_MOVES];
extern int numMovimientos;

#endif
