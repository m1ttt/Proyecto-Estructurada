#include "../prototipos/materiales.h"
#include <stdio.h>

Move posiblesMovimientos[MAX_MOVES];  // Definición real
int numMovimientos = 0;               // Inicialización


void agregarMovimiento(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        posiblesMovimientos[numMovimientos].x = x;
        posiblesMovimientos[numMovimientos].y = y;
        numMovimientos++;
    }
}

void obtenerMovimientos(Pieza p) {
    numMovimientos = 0;  // Reinicia la cuenta de movimientos
    int knightMoves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    switch (p.tipo) {
        case 'P':  // Peón
            // Movimientos típicos hacia adelante; no incluye captura ni promoción
            agregarMovimiento(p.coordenadaX, p.coordenadaY + (p.color == 0 ? 1 : -1));
            break;
        case 'R':  // Rey
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 || dy != 0) {
                        agregarMovimiento(p.coordenadaX + dx, p.coordenadaY + dy);
                    }
                }
            }
            break;
        case 'Q':  // Reina
            for (int i = 1; i < 8; i++) {  // Movimientos horizontales, verticales y diagonales
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY);
                agregarMovimiento(p.coordenadaX, p.coordenadaY + i);
                agregarMovimiento(p.coordenadaX, p.coordenadaY - i);
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY + i);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY - i);
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY - i);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY + i);
            }
            break;
        case 'T':  // Torre
            for (int i = 1; i < 8; i++) {  // Movimientos horizontales y verticales
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY);
                agregarMovimiento(p.coordenadaX, p.coordenadaY + i);
                agregarMovimiento(p.coordenadaX, p.coordenadaY - i);
            }
            break;
        case 'A':  // Alfil
            for (int i = 1; i < 8; i++) {  // Movimientos diagonales
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY + i);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY - i);
                agregarMovimiento(p.coordenadaX + i, p.coordenadaY - i);
                agregarMovimiento(p.coordenadaX - i, p.coordenadaY + i);
            }
            break;
        case 'C':  // Caballo
            // Movimientos en L
           
            for (int i = 0; i < 8; i++) {
                agregarMovimiento(p.coordenadaX + knightMoves[i][0], p.coordenadaY + knightMoves[i][1]);
            }
            break;
    }
}


int esMovimientoValido(int x, int y) {
    for (int i = 0; i < numMovimientos; i++) {
        if (posiblesMovimientos[i].x == x && posiblesMovimientos[i].y == y) {
            return 1;  // El movimiento es válido
        }
    }
    return 0;  // El movimiento no es válido
}


void moverPieza(Tablero* tablero, Pieza* pieza, int newX, int newY) {
    obtenerMovimientos(*pieza);  // Obtiene los movimientos válidos para la pieza

    if (esMovimientoValido(newX, newY)) {
        if (tablero->casillas[newX][newY] == NULL) {  // Verifica que la casilla destino esté vacía
            tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;  // Limpia la casilla actual
            pieza->coordenadaX = newX;  // Actualiza la posición de la pieza
            pieza->coordenadaY = newY;
            tablero->casillas[newX][newY] = pieza;  // Coloca la pieza en la nueva posición
        } else {
            printf("La casilla destino (%d, %d) está ocupada.\n", newX, newY);
        }
    } else {
        printf("Movimiento no válido para la pieza %c.\n", pieza->tipo);
    }
}
