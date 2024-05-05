#ifndef MENU_H
#define MENU_H

void inicializarMenu();
void limpiezaDePantalla();
void menu();


typedef struct {
  char *nombre;
  void (*funcion)();
} OpcionesMenu;


#endif