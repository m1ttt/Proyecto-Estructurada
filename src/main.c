#include "prototipos/acciones.h"
#include "prototipos/materiales.h"
#include "prototipos/menu.h"
#include <stdio.h>

int main() {

  // inicializarMenu();
  Tablero *tablero = inicializarTableroBackend();
  Pieza *piezasBlancas = crearPiezasBlancas();
  Pieza *piezasNegras = crearPiezasNegras();
  colocarPiezasEnTablero(tablero, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  printf("Las piezas blancas son: \n");
  for (int i = 0; i < 16; i++) {
    printf("Pieza %d: %c\n", i, piezasBlancas[i].tipo);
  }

  Move *movimientos = obtenerMovimientosArray(tablero, &piezasBlancas[8], piezasBlancas, piezasNegras);
  printf("Los movimientos posibles son: \n");
  for (int i = 0; i < numMovimientos; i++) {
    printf("Movimiento %d: %d, %d\n", i, movimientos[i].x, movimientos[i].y);
  }
  return 0;
}

