#ifndef ACCIONES_H
#define ACCIONES_H
#define IMG_GUI_HEIGHT 80 // Tamaño de las imágenes en la GUI
#define IMG_GUI_WIDTH 80  // Tamaño de las imágenes en la GUI
#define IMG_SRC_LOCATION "src/assets/piezas/" // Ubicación de las imágenes
#define IMG_SRC_EXTENSION ".png"              // Extensión de las imágenes
#define TURNO_BLANCO 0
#define TURNO_NEGRO 1

#include "gui.h"
#include "materiales.h"

typedef enum { JUGADOR1, JUGADOR2 } Turno; 
typedef struct {
  Move posiblesMovimientos[MAX_MOVES]; 
  int numMovimientos;
} Movimientos;

/**
 * Estructura para almacenar los datos de una casilla en el tablero de ajedrez.
 */
typedef struct {
  int x;                      /**< Coordenada x de la casilla en el tablero. */
  int y;                      /**< Coordenada y de la casilla en el tablero. */
  GtkWidget *grid;            /**< Puntero al widget de la cuadrícula que contiene la casilla. */
  GtkWidget *labelTurno;      /**< Puntero al widget de la etiqueta que muestra el turno actual. */
  GtkWidget *botonSeleccionado; /**< Puntero al widget del botón que ha sido seleccionado en la casilla. */
  Pieza *piezasBlancas;       /**< Puntero al array de piezas blancas en el tablero. */
  Pieza *piezasNegras;        /**< Puntero al array de piezas negras en el tablero. */
  Tablero *tablero;           /**< Puntero al tablero de ajedrez. */
  Turno turno;                /**< Turno actual en el juego. */
} DatosCasilla;

#define posiblesMovimientos (movimientosActuales.posiblesMovimientos) 
#define numMovimientos (movimientosActuales.numMovimientos) /* DEFINICIONES DE ESTRUCTURA PARA EVITAR USO DE GLOBAL*/


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
