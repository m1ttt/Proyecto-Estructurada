#ifndef ACCIONES_H
#define ACCIONES_H

#include "materiales.h" // Asegúrate de incluir las dependencias necesarias
#include "gui.h"

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
void generacion_tablero_gui();

#endif // ACCIONES_H
