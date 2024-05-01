#include "prototipos/materiales.h"
#include "prototipos/menu.h"

int main() {
  inicializarMenu();
  return 0;
}



/*

Ejemplo

Pieza rey = {4, 4, 0, 'R', 0};  // Ejemplo con un Rey blanco
    obtenerMovimientos(rey);

    printf("Movimientos posibles para %c en (%d, %d):\n", rey.tipo, rey.coordenadaX, rey.coordenadaY);
    for (int i = 0; i < numMovimientos; i++) {
        printf("(%d, %d)\n", posiblesMovimientos[i].x, posiblesMovimientos[i].y);
    }

    return 0;


*/