#ifndef ACCIONES_H
#define ACCIONES_H

#include "materiales.h" // Asegúrate de incluir las dependencias necesarias

// Declara aquí todas las funciones de acciones.c que quieras exponer
void agregarMovimiento(int x, int y);
void obtenerMovimientos(Tablero *tablero, Pieza *p, Pieza *piezasAliadas, Pieza *piezasEnemigas);

int esMovimientoValido(int x, int y);
int moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY, Pieza *piezasAliadas, Pieza *piezasEnemigas);
void imprimirTablero(Tablero *tablero);
void inicializarTablero(GtkWidget *grid, Pieza *piezasBlancas,
                        Pieza *piezasNegras);
Pieza *crearPiezasBlancas();
Pieza *crearPiezasNegras();
void obtenerNombreImagen(char *nombreImagen, char pieza, int color);
Move *obtenerMovimientosArray(Tablero *tablero, Pieza *p, Pieza *piezasAliadas, Pieza *piezasEnemigas);
int Check4Checks(Pieza *piezas, Tablero *tablero, Pieza *piezasAliadas);
#endif // ACCIONES_H
