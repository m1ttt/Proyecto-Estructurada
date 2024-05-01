#include "../prototipos/menu.h"
#include "../prototipos/sistema.h"
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *nombre;
  void (*funcion)();
} OpcionesMenu;

void jugar() {}

void salir() {
  endwin();
  exit(0);
}

OpcionesMenu opciones[] = {{"Jugar", jugar}, {"Salir", salir}};

void inicializarMenu() {
  limpiezaDePantalla();
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  int seleccion = 0;
  int ch;

  while (1) {
    for (int i = 0; i < sizeof(opciones) / sizeof(OpcionesMenu); i++) {
      if (i == seleccion) {
        attron(A_REVERSE);
      }
      mvprintw(i + 1, 1, opciones[i].nombre);
      attroff(A_REVERSE);
    }

    ch = getch();
    switch (ch) {
    case KEY_UP:
      seleccion--;
      if (seleccion < 0) {
        seleccion = 0;
      }
      break;
    case KEY_DOWN:
      seleccion++;
      if (seleccion >= sizeof(opciones) / sizeof(OpcionesMenu)) {
        seleccion = sizeof(opciones) / sizeof(OpcionesMenu) - 1;
      }
      break;
    case 10:
      opciones[seleccion].funcion();
      break;
    }
  }
}

void limpiezaDePantalla() {
  int sistema = detectorDeSistema();
  if (sistema == 1) {
    system("cls");
  } else {
    system("clear");
  }
}