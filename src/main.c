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
    printf("%c %d\n", piezasBlancas[i].tipo, i);
  }
  moverPieza(tablero, &piezasBlancas[6], 6, 4, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[13], 6, 6, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[13], 1, 1, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[13], 1, 2, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[3], 3, 4, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[14], 3, 5, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[14], 4, 4, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasBlancas[14], 4, 1, piezasBlancas, piezasNegras);
  imprimirTablero(tablero);
  moverPieza(tablero, &piezasNegras[0], 0, 2, piezasNegras, piezasBlancas);
  imprimirTablero(tablero);




  return 0;
}
