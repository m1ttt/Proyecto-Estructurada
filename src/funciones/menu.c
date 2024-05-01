#include "../prototipos/menu.h"
#include "../prototipos/sistema.h"

#include <stdio.h>
#include <stdlib.h>

void jugar() { limpiezaDePantalla(); }

void salir() {

  exit(0);
}

OpcionesMenu opciones[] = {{"Jugar", jugar}, {"Salir", salir}};

void inicializarMenu() {


}

void limpiezaDePantalla() {
  int sistema = detectorDeSistema();
  if (sistema == 1) {
    system("cls");
  } else {
    system("clear");
  }
}