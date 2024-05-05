#ifndef MENU_H
#define MENU_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>


void inicializarMenu();
void limpiezaDePantalla();
void menu();


typedef struct {
  char *nombre;
  void (*funcion)();
} OpcionesMenu;


#endif