#include "../prototipos/materiales.h"
#include <stdio.h>
#include "../prototipos/acciones.h"

Move posiblesMovimientos[MAX_MOVES];  // Definición real
int numMovimientos = 0;               // Inicialización


void agregarMovimiento(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        posiblesMovimientos[numMovimientos].x = x;
        posiblesMovimientos[numMovimientos].y = y;
        numMovimientos++;
    }
}

void obtenerMovimientos(Tablero* tablero, Pieza* p) {
    numMovimientos = 0;  // Reinicia la cuenta de movimientos
    int knightMoves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    switch (p->tipo) {
        case 'P':  // Peón
            // Considera capturas y avance normal
            int direction = 0;
            if(p->color == 0){
                direction = 1;
            }else{
                direction = -1;
            }
            int startRow = 0;
            if(p->color == 0){
                startRow = 1;
            }else{
                startRow = -6;
            }
            int nextY = p->coordenadaY + direction;
            if (tablero->casillas[p->coordenadaX][nextY] == NULL) {
                agregarMovimiento(p->coordenadaX, nextY);
                // Verificar si el peón está en la posición inicial y puede avanzar dos casillas
                if (p->coordenadaY == startRow && tablero->casillas[p->coordenadaX][nextY + direction] == NULL) {
                    agregarMovimiento(p->coordenadaX, nextY + direction);
                }
            }
            // Agregar capturas diagonales
            for (int dx = -1; dx <= 1; dx += 2) {
                int captureX = p->coordenadaX + dx;
                if (captureX >= 0 && captureX < 8 && tablero->casillas[captureX][nextY] != NULL &&
                    tablero->casillas[captureX][nextY]->color != p->color) {
                    agregarMovimiento(captureX, nextY);
                }
            }
            break;
        case 'R':  // Rey
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 || dy != 0) {
                        int newX = p->coordenadaX + dx;
                        int newY = p->coordenadaY + dy;
                        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
                            (tablero->casillas[newX][newY] == NULL || tablero->casillas[newX][newY]->color != p->color)) {
                            agregarMovimiento(newX, newY);
                        }
                    }
                }
            }
            break;
        case 'Q':  // Reina
        case 'T':  // Torre
        case 'A':  // Alfil
            // Se manejan juntos porque la Reina combina los movimientos de la Torre y el Alfil
            int directions[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},  // movimientos de la Torre
                                   {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};  // movimientos del Alfil
            int numDirections = (p->tipo == 'Q') ? 8 : (p->tipo == 'T' ? 4 : 4);
            for (int i = 0; i < numDirections; i++) {
                int dx = directions[i][0], dy = directions[i][1];
                for (int j = 1; j < 8; j++) {
                    int newX = p->coordenadaX + j * dx;
                    int newY = p->coordenadaY + j * dy;
                    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) break;  // Salir si se sale del tablero
                    if (tablero->casillas[newX][newY] != NULL) {
                        if (tablero->casillas[newX][newY]->color != p->color) {
                            agregarMovimiento(newX, newY);
                        }
                        break;  // Detenerse al encontrar cualquier pieza
                    }
                    agregarMovimiento(newX, newY);
                }
            }
            break;
        case 'C':  // Caballo
            for (int i = 0; i < 8; i++) {
                int newX = p->coordenadaX + knightMoves[i][0];
                int newY = p->coordenadaY + knightMoves[i][1];
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
                    (tablero->casillas[newX][newY] == NULL || tablero->casillas[newX][newY]->color != p->color)) {
                    agregarMovimiento(newX, newY);
                }
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
    obtenerMovimientos(tablero, pieza);  // Corrige el paso de argumentos

    if (esMovimientoValido(newX, newY)) {
        if (tablero->casillas[newX][newY] == NULL) {  // Verifica que la casilla destino esté vacía
            tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;  // Limpia la casilla actual
            pieza->coordenadaX = newX;  // Actualiza la posición de la pieza
            pieza->coordenadaY = newY;
            tablero->casillas[newX][newY] = pieza;  // Coloca la pieza en la nueva posición
            printf("Pieza movida a (%d, %d).\n", newX, newY);
        } else if (tablero->casillas[newX][newY]->color != pieza->color) {
            // Aquí puedes agregar lógica para manejar la captura de una pieza enemiga
            printf("Pieza capturada en (%d, %d).\n", newX, newY);
            tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;  // Limpia la casilla actual
            pieza->coordenadaX = newX;  // Actualiza la posición de la pieza
            pieza->coordenadaY = newY;
            tablero->casillas[newX][newY] = pieza;  // Coloca la pieza en la nueva posición
        } else {
            printf("La casilla destino (%d, %d) está ocupada por una pieza amiga.\n", newX, newY);
        }
    } else {
        printf("Movimiento no válido para la pieza %c.\n", pieza->tipo);
    }
}
