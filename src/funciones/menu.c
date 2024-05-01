#include "../prototipos/menu.h"
#include "../prototipos/sistema.h"
#include <stdlib.h>
#include <stdio.h>

void inicializarMenu() {
  
  limpiezaDePantalla();
}

void limpiezaDePantalla() {
  int sistema = detectorDeSistema();
  if (sistema == 1) {
    system("cls");
  } else {
    system("clear");
  }
}