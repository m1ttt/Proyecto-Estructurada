#ifndef MATERIALES_H
#define MATERIALES_H


#define MAX_MOVES 28  // Número máximo de movimientos posibles en una jugada, como para la Reina

typedef struct {
    int x;
    int y;
} Move;

typedef struct {
    int coordenadaX;
    int coordenadaY;
    int valor;
    char tipo;  // P, R, Q, T, A, C
    int color; // 0: blanco, 1: Negro
    int capturada;
} Pieza;


typedef struct {
    Pieza* casillas[8][8];
} Tablero;

extern Move posiblesMovimientos[MAX_MOVES];
extern int numMovimientos;

#endif


