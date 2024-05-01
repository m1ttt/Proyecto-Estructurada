#ifndef MENU_H
#define MENU_H

void inicializarMenu();
void limpiezaDePantalla();

typedef struct {
  char *nombre;
  void (*funcion)();
} OpcionesMenu;

#endif