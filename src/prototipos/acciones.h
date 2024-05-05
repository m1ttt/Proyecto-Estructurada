#ifndef ACCIONES_H
#define ACCIONES_H

#include "gui.h"
#include "materiales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declara aquí todas las funciones de acciones.c que quieras exponer
void agregarMovimiento(int x, int y);
void obtenerMovimientos(Tablero *tablero, Pieza *p);
int esMovimientoValido(int x, int y);
void moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY);
void imprimirTablero(Tablero *tablero);
void inicializarTablero(GtkWidget *grid, Pieza *piezasBlancas,
                        Pieza *piezasNegras);
Pieza *crearPiezasBlancas();
Pieza *crearPiezasNegras();
void obtenerNombreImagen(char *nombreImagen, char pieza, int color);
Move *obtenerMovimientosArray(Tablero *tablero, Pieza *p);
void generacionTableroGUI();
void desplegarMovimientosGUI(GtkWidget *grid, int x, int y,
                             Pieza *piezasBlancas, Pieza *piezasNegras);
void on_casilla_clicked(GtkWidget *casilla, gpointer grid);

typedef struct {
  Move posiblesMovimientos[MAX_MOVES];
  int numMovimientos;
} Movimientos;

#endif // ACCIONES_H
