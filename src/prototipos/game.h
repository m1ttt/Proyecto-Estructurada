#ifndef GAME_H
#define GAME_H

#include "acciones.h"
#include "sistema.h"

void generacionTableroGUI();
void on_casilla_clicked(GtkWidget *casilla, gpointer grid);
void desplegarMovimientosGUI(GtkWidget *grid, int x, int y, Pieza *pieza,
                             Pieza *piezasBlancas, Pieza *piezasNegras,
                             Tablero *tablero);
void button_toggled(GtkToggleButton *button, gpointer user_data);
void actualizarLabelTurno(GtkWidget *labelTurno, int turno);
void actualizarPosiciones(DatosCasilla *datos);
void inicializarTablero(GtkWidget *grid, Pieza *piezasBlancas,
                        Pieza *piezasNegras);
                        
#endif