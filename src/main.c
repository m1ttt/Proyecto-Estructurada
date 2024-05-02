#include "prototipos/acciones.h"
#include "prototipos/materiales.h"
#include "prototipos/menu.h"
#include <stdio.h>

int main() {
  inicializarMenu();

  Tablero tablero;
  Pieza *piezasBlancas = crearPiezasBlancas();
  Pieza *piezasNegras = crearPiezasNegras();
  inicializarTablero(&tablero, piezasBlancas, piezasNegras);
  imprimirTablero(&tablero);

  /* Ejemplo de movimiento
  Pieza peon = piezasBlancas[0];
  moverPieza(&tablero, &peon, 0, 4);
  imprimirTablero(&tablero);
*/

  return 0;
}

/*El tablero tiene la siguiente estructura

x-------------> y
0 1 2 3 ... 7   |
              1 |
              2 |
              3 |
              . |
              . |
              . |
              7 v

*/