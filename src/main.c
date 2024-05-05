#include "prototipos/acciones.h"
#include "prototipos/materiales.h"
#include "prototipos/menu.h"
#include <stdio.h>

int main() {
  // inicializarMenu();
  Tablero tablero;
  //Hacer 2 peones en un array de piezas blancas
  Pieza peonesBlancos[2];
  //Hacer 2 peones en un array de piezas negras
  Pieza piezasNegros[2];

  peonesBlancos[0] = (Pieza){.imagen = NULL, .tipo = 'T', .color = 0, .coordenadaX = 0, .coordenadaY = 0, .capturada = 0};
  peonesBlancos[1] = (Pieza){.imagen = NULL, .tipo = 'T', .color = 0, .coordenadaX = 1, .coordenadaY = 0, .capturada = 0};
  //Hacer el tablero vacio
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      tablero.casillas[i][j] = NULL;
    }
  }
  //Poner los peones en el tablero
  tablero.casillas[0][0] = &peonesBlancos[0];
  tablero.casillas[1][0] = &peonesBlancos[1];
  //Imprimir el tablero
  piezasNegros[0] = (Pieza){.imagen = NULL, .tipo = 'T', .color = 1, .coordenadaX = 0, .coordenadaY = 7, .capturada = 0};
  piezasNegros[1] = (Pieza){.imagen = NULL, .tipo = 'R', .color = 1, .coordenadaX = 1, .coordenadaY = 7, .capturada = 0};
  tablero.casillas[0][7] = &piezasNegros[0];
  tablero.casillas[1][7] = &piezasNegros[1];
  imprimirTablero(&tablero);
  //int moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY, Pieza *piezasAliadas, Pieza *piezasEnemigas);
  int a = moverPieza(&tablero, &piezasNegros[0], 1, 0, piezasNegros, peonesBlancos);
printf("%d\n", a);
  imprimirTablero(&tablero);
  int b = moverPieza(&tablero, &piezasNegros[1], 1, 6, piezasNegros, peonesBlancos);
  printf("%d\n", b);
  imprimirTablero(&tablero);
  return 0;
}

