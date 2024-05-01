#include "prototipos/materiales.h"
#include "prototipos/menu.h"
#include "prototipos/acciones.h"
#include <stdio.h>
/*NOTA:
Cada pieza define su tipo con una char, siendo:
P: Peón
R: Rey
Q: Reina
T: Torre
A: Alfil
C: Caballo
*/

int main() {
   inicializarMenu();



  //Ejemplo de uso de las funciones de ajedrez///////////////////////////////////////////////////////////////////
  Tablero tablero;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero.casillas[i][j] = NULL;  
        }
    }

    // Crear algunas piezas
    Pieza peonBlanco = {1, 1, 1, 'P', 0}; // CoordenadaX, CoordenadaY, valor, tipo, color
    Pieza torreNegra = {0, 1, 5, 'T', 1}; // CoordenadaX, CoordenadaY, valor, tipo, color

    // Colocar las piezas en el tablero
    tablero.casillas[peonBlanco.coordenadaX][peonBlanco.coordenadaY] = &peonBlanco;
    tablero.casillas[torreNegra.coordenadaX][torreNegra.coordenadaY] = &torreNegra;

    printf("Intentando mover el peón blanco \n");
    moverPieza(&tablero, &peonBlanco, 1, 3);

    if (tablero.casillas[1][3] == &peonBlanco) {
        printf("Movimiento exitoso.\n");
    } else {
        printf("Movimiento fallido.\n");
    }

    printf("Intentando mover la torre negra\n");
    moverPieza(&tablero, &torreNegra, 3, 1);

    if (tablero.casillas[3][1] == &torreNegra) {
        printf("Movimiento exitoso.\n");
    } else {
        printf("Movimiento fallido.\n");
    }
//Fin del ejemplo /////////////////////////////////////////////////////////////////////////
    return 0;
}

