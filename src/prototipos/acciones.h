#ifndef ACCIONES_H
#define ACCIONES_H

#include "gui.h"
#include "materiales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct {
  Move posiblesMovimientos[MAX_MOVES];
  int numMovimientos;
} Movimientos;

typedef enum { JUGADOR1, JUGADOR2 } Turno;
typedef enum { B, N } Color;

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
void colocarPiezaEnCasilla(Pieza *pieza, GtkWidget *grid);
void actualizarLabelTurno(GtkWidget *labelTurno, int turno);
// Declara aquí todas las funciones de acciones.c que quieras exponer
void agregarMovimiento(int x, int y);
void obtenerMovimientos(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                        Pieza *piezasEnemigas);

int esMovimientoValido(int x, int y);
int moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY,
               Pieza *piezasAliadas, Pieza *piezasEnemigas);
void inicializarTablero(GtkWidget *grid, Pieza *piezasBlancas,
                        Pieza *piezasNegras);
Pieza *crearPiezasBlancas();
Pieza *crearPiezasNegras();
void obtenerNombreImagen(char *nombreImagen, char pieza, int color);
Move *obtenerMovimientosArray(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                              Pieza *piezasEnemigas);
void generacionTableroGUI();
void desplegarMovimientosGUI(GtkWidget *grid, int x, int y, Pieza *pieza,
                             Pieza *piezasBlancas, Pieza *piezasNegras,
                             Tablero *tablero);
void on_casilla_clicked(GtkWidget *casilla, gpointer grid);
Pieza *buscarPieza(int x, int y, Pieza *piezasBlancas, Pieza *piezasNegras);
Tablero *inicializarTableroBackend();
void button_toggled(GtkToggleButton *button, gpointer user_data);

void actualizarPosiciones(DatosCasilla *datos);
int Check4Checks(Pieza *piezas, Tablero *tablero, Pieza *piezasAliadas);
void colocarPiezasEnTablero(Tablero *tablero, Pieza *piezasBlancas,
                            Pieza *piezasNegras);
void imprimirTablero(Tablero *tablero);
int esJaqueMate(Tablero *tablero, Pieza *piezasAliadas, Pieza *piezasEnemigas);
Tablero *copiarTablero(Tablero *tablero);
Pieza *copiarPiezas(Pieza *pieza);

#endif // ACCIONES_H
