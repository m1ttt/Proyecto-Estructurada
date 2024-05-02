#ifndef ACCIONES_H
#define ACCIONES_H

#include "materiales.h"  // Asegúrate de incluir las dependencias necesarias

// Declara aquí todas las funciones de acciones.c que quieras exponer
void agregarMovimiento(int x, int y);
void obtenerMovimientos(Tablero* tablero, Pieza* p);
int esMovimientoValido(int x, int y);
void moverPieza(Tablero* tablero, Pieza* pieza, int newX, int newY);
void imprimirTablero(Tablero* tablero);
void inicializarTablero(Tablero* tablero, Pieza* piezasBlancas, Pieza* piezasNegras);
Pieza* crearPiezasBlancas();
Pieza* crearPiezasNegras();


#endif // ACCIONES_H
