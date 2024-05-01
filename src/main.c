#include "prototipos/materiales.h"
#include "prototipos/menu.h"
#include "prototipos/acciones.h"
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
      Tablero tablero = {0};  // Inicializa el tablero con todas las casillas vacías

  Pieza rey = {4, 4, 0, 'R', 0};  // Ejemplo con un Rey blanco
    obtenerMovimientos(rey);

    printf("Movimientos posibles para %c en (%d, %d):\n", rey.tipo, rey.coordenadaX, rey.coordenadaY);
    for (int i = 0; i < numMovimientos; i++) {
        printf("(%d, %d)\n", posiblesMovimientos[i].x, posiblesMovimientos[i].y);
    }
    moverPieza(&tablero, &rey, 4, 5);

    return 0;
}
