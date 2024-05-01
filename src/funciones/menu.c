#include "../prototipos/menu.h"
#include "../prototipos/sistema.h"
#include <stdio.h>
#include <stdlib.h>

/*NOTA:
Cada pieza define su tipo con una char, siendo:
P: Peón
R: Rey
Q: Reina
T: Torre
A: Alfil
C: Caballo
// Crear algunas piezas
    Pieza peonBlanco = {1, 1, 1, 'P', 0, 0}; // CoordenadaX, CoordenadaY, valor,
tipo, color, capturada Pieza torreNegra = {1, 6, 5, 'T', 1, 0}; // CoordenadaX,
CoordenadaY, valor, tipo, color, capturada
*/

void jugar() { limpiezaDePantalla(); }

void salir() { exit(0); }

OpcionesMenu opciones[] = {{"Jugar", jugar}, {"Salir", salir}};

void inicializarMenu() {}

void limpiezaDePantalla() {
  int sistema = detectorDeSistema();
  if (sistema == 1) {
    system("cls");
  } else {
    system("clear");
  }
}