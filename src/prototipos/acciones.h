#ifndef ACCIONES_H
#define ACCIONES_H
#define IMG_GUI_HEIGHT 80
#define IMG_GUI_WIDTH 80
#define IMG_SRC_LOCATION "src/assets/piezas/"
#define IMG_SRC_EXTENSION ".png"
#define TURNO_BLANCO 0
#define TURNO_NEGRO 1

#include "gui.h"
#include "materiales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { JUGADOR1, JUGADOR2 } Turno;
typedef enum { B, N } Color;
typedef struct {
  Move posiblesMovimientos[MAX_MOVES];
  int numMovimientos;
} Movimientos;

typedef struct {
  int x;
  int y;
  GtkWidget *grid;
  GtkWidget *labelTurno;
  GtkWidget *botonSeleccionado;
  Pieza *piezasBlancas;
  Pieza *piezasNegras;
  Tablero *tablero;
  Turno turno;
} DatosCasilla;

#define posiblesMovimientos (movimientosActuales.posiblesMovimientos)
#define numMovimientos (movimientosActuales.numMovimientos)

// Declara aquí todas las funciones de acciones.c que quieras exponer
void agregarMovimiento(int x, int y);
void obtenerMovimientos(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                        Pieza *piezasEnemigas);
int esMovimientoValido(int x, int y);
int moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY,
               Pieza *piezasAliadas, Pieza *piezasEnemigas);

Pieza *crearPiezasBlancas();
Pieza *crearPiezasNegras();
void obtenerNombreImagen(char *nombreImagen, char pieza, int color);
Move *obtenerMovimientosArray(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                              Pieza *piezasEnemigas);
Pieza *buscarPieza(int x, int y, Pieza *piezasBlancas, Pieza *piezasNegras);
Tablero *inicializarTableroBackend();
int Check4Checks(Pieza *piezas, Tablero *tablero, Pieza *piezasAliadas);
void colocarPiezasEnTablero(Tablero *tablero, Pieza *piezasBlancas,
                            Pieza *piezasNegras);
void imprimirTablero(Tablero *tablero);
int esJaqueMate(Tablero *tablero, Pieza *piezasAliadas, Pieza *piezasEnemigas);
Tablero *copiarTablero(Tablero *tablero);
Pieza *copiarPiezas(Pieza *pieza);

extern Movimientos movimientosActuales;

#endif // ACCIONES_H
