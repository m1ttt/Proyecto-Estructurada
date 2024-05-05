#ifndef MENU_H
#define MENU_H

void inicializarMenu();
void limpiezaDePantalla();
void menu();
void generacion_tablero_gui();

typedef struct {
  char *nombre;
  void (*funcion)();
} OpcionesMenu;


#endif