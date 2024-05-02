#include "../prototipos/acciones.h"
#include "../prototipos/materiales.h"
#include <stdio.h>
#include <stdlib.h>

Move posiblesMovimientos[MAX_MOVES]; // Definición real
int numMovimientos = 0;              // Inicialización

void agregarMovimiento(int x, int y) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    posiblesMovimientos[numMovimientos].x = x;
    posiblesMovimientos[numMovimientos].y = y;
    numMovimientos++;
  }
}

void obtenerMovimientos(Tablero *tablero, Pieza *p) {
    //Verifica que la pieza no haya sido capturada
    if (p->capturada) {
        printf("La pieza %c ya fue capturada.\n", p->tipo);
        return;
    }
  numMovimientos = 0; // Reinicia la cuenta de movimientos
  int knightMoves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                           {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

  switch (p->tipo) {
  case 'P': {
    int direction = (p->color == 0 ? 1 : -1);
    int startRow = (p->color == 0 ? 1 : 6);
    int nextY = p->coordenadaY + direction;
    if (tablero->casillas[p->coordenadaX][nextY] == NULL) {
      agregarMovimiento(p->coordenadaX, nextY);
      // Verificar si el peón está en la posición inicial y puede avanzar dos
      // casillas
      if (p->coordenadaY == startRow &&
          tablero->casillas[p->coordenadaX][nextY + direction] == NULL) {
        agregarMovimiento(p->coordenadaX, nextY + direction);
      }
    }
    // Agregar capturas diagonales
    for (int dx = -1; dx <= 1; dx += 2) {
      int captureX = p->coordenadaX + dx;
      if (captureX >= 0 && captureX < 8 &&
          tablero->casillas[captureX][nextY] != NULL &&
          tablero->casillas[captureX][nextY]->color != p->color) {
        agregarMovimiento(captureX, nextY);
      }
    }
  } break;
  case 'R': // Rey
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (dx != 0 || dy != 0) {
          int newX = p->coordenadaX + dx;
          int newY = p->coordenadaY + dy;
          if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
              (tablero->casillas[newX][newY] == NULL ||
               tablero->casillas[newX][newY]->color != p->color)) {
            agregarMovimiento(newX, newY);
          }
        }
      }
    }
    break;
  case 'Q': // Reina
  case 'T': // Torre
  case 'A': // Alfil
            // Se manejan juntos porque la Reina combina los movimientos de la
            // Torre y el Alfil
  {
    int directions[][2] = {
        {1, 0}, {-1, 0},  {0, 1},  {0, -1},  // movimientos de la Torre
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // movimientos del Alfil
    int numDirections = (p->tipo == 'Q') ? 8 : (p->tipo == 'T' ? 4 : 4);
    for (int i = 0; i < numDirections; i++) {
      int dx = directions[i][0], dy = directions[i][1];
      for (int j = 1; j < 8; j++) {
        int newX = p->coordenadaX + j * dx;
        int newY = p->coordenadaY + j * dy;
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
          break; // Salir si se sale del tablero
        if (tablero->casillas[newX][newY] != NULL) {
          if (tablero->casillas[newX][newY]->color != p->color) {
            agregarMovimiento(newX, newY);
          }
          break; // Detenerse al encontrar cualquier pieza
        }
        agregarMovimiento(newX, newY);
      }
    }
  } break;
  case 'C': // Caballo
    for (int i = 0; i < 8; i++) {
      int newX = p->coordenadaX + knightMoves[i][0];
      int newY = p->coordenadaY + knightMoves[i][1];
      if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
          (tablero->casillas[newX][newY] == NULL ||
           tablero->casillas[newX][newY]->color != p->color)) {
        agregarMovimiento(newX, newY);
      }
    }
    break;
  }
}

int esMovimientoValido(int x, int y) {
  for (int i = 0; i < numMovimientos; i++) {
    if (posiblesMovimientos[i].x == x && posiblesMovimientos[i].y == y) {
      return 1; // El movimiento es válido
    }
  }
  return 0; // El movimiento no es válido
}


void moverPieza(Tablero* tablero, Pieza* pieza, int newX, int newY) {
    obtenerMovimientos(tablero, pieza);  // Corrige el paso de argumentos
    if (pieza->capturada) {
        printf("La pieza %c ya fue capturada.\n", pieza->tipo);
        return;
    }
    if (esMovimientoValido(newX, newY)) {
        if (tablero->casillas[newX][newY] == NULL) {  // Verifica que la casilla destino esté vacía
            tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;  // Limpia la casilla actual
            pieza->coordenadaX = newX;  // Actualiza la posición de la pieza
            pieza->coordenadaY = newY;
            tablero->casillas[newX][newY] = pieza;  // Coloca la pieza en la nueva posición
            printf("Pieza movida a (%d, %d).\n", newX, newY);
        } else if (tablero->casillas[newX][newY]->color != pieza->color) {
            // Aquí puedes agregar lógica para manejar la captura de una pieza enemiga
            printf("Pieza capturada en (%d, %d).\n", newX, newY);
            tablero->casillas[newX][newY]->capturada = 1;  // Marca la pieza como capturada
            tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;  // Limpia la casilla actual
            pieza->coordenadaX = newX;  // Actualiza la posición de la pieza
            pieza->coordenadaY = newY;
            tablero->casillas[newX][newY] = pieza;  // Coloca la pieza en la nueva posición
        } else {
            printf("La casilla destino (%d, %d) está ocupada por una pieza amiga.\n", newX, newY);
        }
    } else {
        printf("Movimiento no válido para la pieza %c.\n", pieza->tipo);
    }
}


//Crear piezas blancas y devolverlas en un arreglo para accederlas
Pieza* crearPiezasNegras() {
    Pieza* piezasNegras = (Pieza*)malloc(16 * sizeof(Pieza));
    //Peones
    for (int i = 0; i < 8; i++) {
        piezasNegras[i].tipo = 'P';
        piezasNegras[i].color = 0;
        piezasNegras[i].coordenadaX = i;
        piezasNegras[i].coordenadaY = 1;
        piezasNegras[i].capturada = 0;
    }
    //Torres
    piezasNegras[8].tipo = 'T';
    piezasNegras[8].color = 0;
    piezasNegras[8].coordenadaX = 0;
    piezasNegras[8].coordenadaY = 0;
    piezasNegras[8].capturada = 0;
    piezasNegras[9].tipo = 'T';
    piezasNegras[9].color = 0;
    piezasNegras[9].coordenadaX = 7;
    piezasNegras[9].coordenadaY = 0;
    piezasNegras[9].capturada = 0;
    //Caballos
    piezasNegras[10].tipo = 'C';
    piezasNegras[10].color = 0;
    piezasNegras[10].coordenadaX = 1;
    piezasNegras[10].coordenadaY = 0;
    piezasNegras[10].capturada = 0;
    piezasNegras[11].tipo = 'C';
    piezasNegras[11].color = 0;
    piezasNegras[11].coordenadaX = 6;
    piezasNegras[11].coordenadaY = 0;
    piezasNegras[11].capturada = 0;
    //Alfiles
    piezasNegras[12].tipo = 'A';
    piezasNegras[12].color = 0;
    piezasNegras[12].coordenadaX = 2;
    piezasNegras[12].coordenadaY = 0;
    piezasNegras[12].capturada = 0;
    piezasNegras[13].tipo = 'A';
    piezasNegras[13].color = 0;
    piezasNegras[13].coordenadaX = 5;
    piezasNegras[13].coordenadaY = 0;
    piezasNegras[13].capturada = 0;
    //Reina
    piezasNegras[14].tipo = 'Q';
    piezasNegras[14].color = 0;
    piezasNegras[14].coordenadaX = 3;
    piezasNegras[14].coordenadaY = 0;
    piezasNegras[14].capturada = 0;
    //Rey
    piezasNegras[15].tipo = 'R';
    piezasNegras[15].color = 0;
    piezasNegras[15].coordenadaX = 4;
    piezasNegras[15].coordenadaY = 0;
    piezasNegras[15].capturada = 0;
    return piezasNegras;
}

Pieza* crearPiezasBlancas() {
    Pieza* piezasBlancas = (Pieza*)malloc(16 * sizeof(Pieza));
    //Peones
    for (int i = 0; i < 8; i++) {
        piezasBlancas[i].tipo = 'P';
        piezasBlancas[i].color = 1;
        piezasBlancas[i].coordenadaX = i;
        piezasBlancas[i].coordenadaY = 6;
        piezasBlancas[i].capturada = 0;
    }
    //Torres
    piezasBlancas[8].tipo = 'T';
    piezasBlancas[8].color = 1;
    piezasBlancas[8].coordenadaX = 7;
    piezasBlancas[8].coordenadaY = 7;
    piezasBlancas[8].capturada = 0;
    piezasBlancas[9].tipo = 'T';
    piezasBlancas[9].color = 1;
    piezasBlancas[9].coordenadaX = 0;
    piezasBlancas[9].coordenadaY = 7;
    piezasBlancas[9].capturada = 0;
    //Caballos
    piezasBlancas[10].tipo = 'C';
    piezasBlancas[10].color = 1;
    piezasBlancas[10].coordenadaX = 1;
    piezasBlancas[10].coordenadaY = 7;
    piezasBlancas[10].capturada = 0;
    piezasBlancas[11].tipo = 'C';
    piezasBlancas[11].color = 1;
    piezasBlancas[11].coordenadaX = 6;
    piezasBlancas[11].coordenadaY = 7;
    piezasBlancas[11].capturada = 0;
    //Alfiles
    piezasBlancas[12].tipo = 'A';
    piezasBlancas[12].color = 1;
    piezasBlancas[12].coordenadaX = 2;
    piezasBlancas[12].coordenadaY = 7;
    piezasBlancas[12].capturada = 0;
    piezasBlancas[13].tipo = 'A';
    piezasBlancas[13].color = 1;
    piezasBlancas[13].coordenadaX = 5;
    piezasBlancas[13].coordenadaY = 7;
    piezasBlancas[13].capturada = 0;
    //Reina
    piezasBlancas[14].tipo = 'Q';
    piezasBlancas[14].color = 1;
    piezasBlancas[14].coordenadaX = 3;
    piezasBlancas[14].coordenadaY = 7;
    piezasBlancas[14].capturada = 0;
    //Rey
    piezasBlancas[15].tipo = 'R';
    piezasBlancas[15].color = 1;
    piezasBlancas[15].coordenadaX = 4;
    piezasBlancas[15].coordenadaY = 7;
    piezasBlancas[15].capturada = 0;
    return piezasBlancas;
}

void inicializarTablero(Tablero* tablero, Pieza* piezasBlancas, Pieza* piezasNegras) {
    // Inicializar todas las casillas a NULL
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero->casillas[i][j] = NULL;
        }
    }
    // Colocar las piezas blancas y negras en el tablero
    for (int i = 0; i < 16; i++) {
        tablero->casillas[piezasBlancas[i].coordenadaX][piezasBlancas[i].coordenadaY] = &piezasBlancas[i];
        tablero->casillas[piezasNegras[i].coordenadaX][piezasNegras[i].coordenadaY] = &piezasNegras[i];
    }
}

void imprimirTablero(Tablero* tablero) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tablero->casillas[j][i] == NULL) {
                printf(". ");
            } else {
                printf("%c ", tablero->casillas[j][i]->tipo);
            }
        }
        printf("\n");
    }
}

