
#include "../prototipos/acciones.h"
#include "../prototipos/materiales.h"
#include "../prototipos/sistema.h"

Movimientos movimientosActuales;

void agregarMovimiento(int x, int y) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    posiblesMovimientos[numMovimientos].x = x;
    posiblesMovimientos[numMovimientos].y = y;
    numMovimientos++;
  }
}

void obtenerMovimientos(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                        Pieza *piezasEnemigas) {
  // Verifica que la pieza no haya sido capturada

  debugMessage("Recibi una pieza de tipo: %c\n", p->tipo);
  if (p->capturada) {
    debugMessage("La pieza %c ya fue capturada.\n", p->tipo);
    return;
  }
  if (Check4Checks(piezasEnemigas, tablero, piezasAliadas) == 1 &&
      p->tipo != 'R') {
    debugMessage("La pieza %c no puede moverse porque el rey está en jaque.\n",
                 p->tipo);

    return;
  }
  numMovimientos = 0; // Reinicia la cuenta de movimientos
  int knightMoves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                           {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

  switch (p->tipo) {
  case 'P': {
    debugMessage("Calculando movimientos para el peón.\n");
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
    debugMessage("Calculando movimientos para el rey.\n");
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
    debugMessage("Calculando movimientos para la reina.\n");
    {

      int directions[][2] = {
          {1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Movimientos de la Torre
      int numDirections =
          (p->tipo == 'Q') ? 4 : 4; // Si es Reina o Torre, son 4 direcciones
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
    }
    debugMessage("Calculando movimientos para el alfil.\n");
    {
      int directions[][2] = {
          {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // Movimientos del Alfil
      for (int i = 0; i < 4;
           i++) { // El Alfil solo tiene 4 direcciones posibles
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
    }
    break;

  case 'T': // Torre
    debugMessage("Calculando movimientos para la torre.\n");
    {
      int directions[][2] = {
          {1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Movimientos de la Torre
      int numDirections =
          (p->tipo == 'Q') ? 4 : 4; // Si es Reina o Torre, son 4 direcciones
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
    }
    break;
  case 'A': // Alfil
    debugMessage("Calculando movimientos para el alfil.\n");
    {
      int directions[][2] = {
          {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // Movimientos del Alfil
      for (int i = 0; i < 4;
           i++) { // El Alfil solo tiene 4 direcciones posibles
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
    }
    break;

  case 'C': // Caballo
    debugMessage("Calculando movimientos para el caballo.\n");
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

void calcularMovimientosSinCheck(Tablero *tablero, Pieza *p) {
  // Verifica que la pieza no haya sido capturada
  debugMessage("Recibi una pieza de tipo: %c\n", p->tipo);
  if (p->capturada) {
    debugMessage("La pieza %c ya fue capturada.\n", p->tipo);
    return;
  }

  numMovimientos = 0; // Reinicia la cuenta de movimientos
  int knightMoves[8][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                           {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

  switch (p->tipo) {
  case 'P': {
    debugMessage("Calculando movimientos para el peón.\n");
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
    debugMessage("Calculando movimientos para el rey.\n");
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
    debugMessage("Calculando movimientos para la reina.\n");
    {

      int directions[][2] = {
          {1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Movimientos de la Torre
      int numDirections =
          (p->tipo == 'Q') ? 4 : 4; // Si es Reina o Torre, son 4 direcciones
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
    }
    debugMessage("Calculando movimientos para el alfil.\n");
    {
      int directions[][2] = {
          {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // Movimientos del Alfil
      for (int i = 0; i < 4;
           i++) { // El Alfil solo tiene 4 direcciones posibles
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
    }
    break;

  case 'T': // Torre
    debugMessage("Calculando movimientos para la torre.\n");
    {
      int directions[][2] = {
          {1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Movimientos de la Torre
      int numDirections =
          (p->tipo == 'Q') ? 4 : 4; // Si es Reina o Torre, son 4 direcciones
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
    }
    break;
  case 'A': // Alfil
    debugMessage("Calculando movimientos para el alfil.\n");
    {
      int directions[][2] = {
          {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}; // Movimientos del Alfil
      for (int i = 0; i < 4;
           i++) { // El Alfil solo tiene 4 direcciones posibles
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
    }
    break;

  case 'C': // Caballo
    debugMessage("Calculando movimientos para el caballo.\n");
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

int Check4Checks(Pieza *piezas, Tablero *tablero, Pieza *piezasAliadas) {
  // Obtener la posicion del rey
  int xRey = 0;
  int yRey = 0;
  for (int i = 0; i < 16; i++) {
    if (piezasAliadas[i].tipo == 'R') {
      xRey = piezasAliadas[i].coordenadaX;
      yRey = piezasAliadas[i].coordenadaY;
      break;
    }
  }
  // Verificar si alguna pieza enemiga puede capturar al rey
  for (int i = 0; i < 16; i++) {
    if (piezas[i].capturada == 0) {
      calcularMovimientosSinCheck(tablero, &piezas[i]);
      for (int j = 0; j < numMovimientos; j++) {
        if (posiblesMovimientos[j].x == xRey &&
            posiblesMovimientos[j].y == yRey) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int esMovimientoValido(int x, int y) {
  for (int i = 0; i < numMovimientos; i++) {
    if (posiblesMovimientos[i].x == x && posiblesMovimientos[i].y == y) {
      return 1; // El movimiento es válido
    }
  }
  return 0; // El movimiento no es válido
}

int moverPieza(Tablero *tablero, Pieza *pieza, int newX, int newY,
               Pieza *piezasAliadas, Pieza *piezasEnemigas) {
  calcularMovimientosSinCheck(tablero, pieza); // Corrige el paso de argumentos
  if (pieza->capturada) {
    debugMessage("La pieza %c ya fue capturada.\n", pieza->tipo);
    return 1;
  }
  if (esMovimientoValido(newX, newY)) {
    // Revisar si el rey entrara en jaque
    if (pieza->tipo == 'R') {
      for (
          int i = 0; i < 16;
          i++) { // CAMBIAR ESTA LINEA EN EL FUTURO A 16
                 // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if (piezasEnemigas[i].capturada == 0) {
          calcularMovimientosSinCheck(tablero, &piezasEnemigas[i]);
          for (int j = 0; j < numMovimientos; j++) {
            if (posiblesMovimientos[j].x == newX &&
                posiblesMovimientos[j].y == newY) {
              debugMessage(
                  "El rey no puede moverse a (%d, %d) porque entraria en "
                  "jaque.\n",
                  newX, newY);
              return 1;
            }
          }
        }
      }
      if (tablero->casillas[newX][newY] ==
          NULL) { // Verifica que la casilla destino esté vacía
        tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] =
            NULL;                  // Limpia la casilla actual
        pieza->coordenadaX = newX; // Actualiza la posición de la pieza
        pieza->coordenadaY = newY;
        tablero->casillas[newX][newY] =
            pieza; // Coloca la pieza en la nueva posición
        debugMessage("Pieza movida a (%d, %d).\n", newX, newY);
        return 0;
      } else if (tablero->casillas[newX][newY]->color != pieza->color) {
        // Aquí puedes agregar lógica para manejar la captura de una pieza
        // enemiga
        debugMessage("Pieza capturada en (%d, %d).\n", newX, newY);
        tablero->casillas[newX][newY]->capturada =
            1; // Marca la pieza como capturada
        tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] =
            NULL;                  // Limpia la casilla actual
        pieza->coordenadaX = newX; // Actualiza la posición de la pieza
        pieza->coordenadaY = newY;
        tablero->casillas[newX][newY] =
            pieza; // Coloca la pieza en la nueva posición
        return 0;
      } else {
        debugMessage(
            "La casilla destino (%d, %d) está ocupada por una pieza amiga.\n",
            newX, newY);
        return 1;
      }
    }

    else if (pieza->tipo == 'P' && (newY == 0 || newY == 7)) {
      pieza->tipo = 'Q';
      pieza->valor = 9;

      // Ver el color de la pieza
      if (pieza->color == 0) {
        // Actualizar la imagen de la pieza
        char nombre_imagen[50];
        obtenerNombreImagen(nombre_imagen, 'Q', 0);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(
            nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
        pieza->imagen = pixbuf;
      } else {
        // Actualizar la imagen de la pieza
        char nombre_imagen[50];
        obtenerNombreImagen(nombre_imagen, 'Q', 1);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(
            nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
        pieza->imagen = pixbuf;
      }
      // Mover la pieza
      tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;
      pieza->coordenadaX = newX;
      pieza->coordenadaY = newY;
      if (tablero->casillas[newX][newY] != NULL) {
        tablero->casillas[newX][newY]->capturada = 1;
      }

      tablero->casillas[newX][newY] = pieza;
      debugMessage("Peon promovido a reina.\n");
      return 0;
    }

    else if (pieza->tipo != 'R') {

      // Guardar las coordenadas actuales de la pieza
      int captura = 0;
      int x = pieza->coordenadaX;
      int y = pieza->coordenadaY;
      if (tablero->casillas[newX][newY] != NULL) {
        if (tablero->casillas[newX][newY]->color != pieza->color) {
          // Hacer una copia de la pieza capturada, para poder revertir el
          // movimiento
          tablero->casillas[newX][newY]->capturada = 1;
          captura = 1;
        } else {
          debugMessage(
              "La casilla destino (%d, %d) está ocupada por una pieza amiga.\n",
              newX, newY);
          return 1;
        }
      }
      // Copiar la pieza que esta en la casilla destino
      Pieza *piezaDestino = tablero->casillas[newX][newY];
      // Hacer un clon de la pieza

      if (captura == 1) {
        tablero->casillas[newX][newY] = NULL;
      }
      // Mover la pieza
      tablero->casillas[x][y] = NULL;
      pieza->coordenadaX = newX;
      pieza->coordenadaY = newY;
      tablero->casillas[newX][newY] = pieza;
      // Verificar si el rey entra en jaque
      if (Check4Checks(piezasEnemigas, tablero, piezasAliadas) == 1) {
        debugMessage(
            "El rey no puede moverse a (%d, %d) porque entraria en jaque2.\n",
            newX, newY);
        // Revertir el movimiento
        tablero->casillas[x][y] = pieza;
        pieza->coordenadaX = x;
        pieza->coordenadaY = y;
        tablero->casillas[newX][newY] = NULL;
        if (captura == 1) {
          tablero->casillas[newX][newY] = piezaDestino;
          tablero->casillas[newX][newY]->capturada = 0;
        }
        return 1;
      }

      // Revertir el movimiento
      tablero->casillas[x][y] = pieza;
      pieza->coordenadaX = x;
      pieza->coordenadaY = y;
      tablero->casillas[newX][newY] = NULL;
      if (captura == 1) {
        tablero->casillas[newX][newY] = piezaDestino;
        tablero->casillas[newX][newY]->capturada = 0;
      }

      if (tablero->casillas[newX][newY] != NULL &&
          tablero->casillas[newX][newY]->tipo == 'R') {
        debugMessage("El rey no puede ser capturado.\n");
        return 1;
      } else if (tablero->casillas[newX][newY] ==
                 NULL) { // Verifica que la casilla destino esté vacía
        tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] =
            NULL;                  // Limpia la casilla actual
        pieza->coordenadaX = newX; // Actualiza la posición de la pieza
        pieza->coordenadaY = newY;
        tablero->casillas[newX][newY] =
            pieza; // Coloca la pieza en la nueva posición
        debugMessage("Pieza movida a (%d, %d).\n", newX, newY);
        return 0;

      } else if (tablero->casillas[newX][newY]->color != pieza->color) {
        // Aquí puedes agregar lógica para manejar la captura de una pieza
        // enemiga
        debugMessage("Pieza capturada en (%d, %d).\n", newX, newY);
        tablero->casillas[newX][newY]->capturada =
            1; // Marca la pieza como capturada
        tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] =
            NULL;                  // Limpia la casilla actual
        pieza->coordenadaX = newX; // Actualiza la posición de la pieza
        pieza->coordenadaY = newY;
        tablero->casillas[newX][newY] =
            pieza; // Coloca la pieza en la nueva posición
        return 0;
      }
    }
  } else {
    debugMessage("Movimiento no válido para la pieza %c.\n", pieza->tipo);
    return 1;
  }
  return 0;
}

void inicializarPieza(Pieza *pieza, char tipo, int color, int valor, int x,
                      int y) {
  pieza->tipo = tipo;
  pieza->color = color;
  pieza->valor = valor;
  pieza->coordenadaX = x;
  pieza->coordenadaY = y;
  pieza->capturada = 0;

  // Inicializar la imagen de la pieza
  char nombre_imagen[50];
  obtenerNombreImagen(nombre_imagen, tipo, color);
  debugMessage(nombre_imagen);

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(
      nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
  pieza->imagen = pixbuf; // Almacenar el GdkPixbuf en lugar de la imagen GTK
}

void obtenerNombreImagen(char *nombreImagen, char pieza, int color) {
  strcpy(nombreImagen, IMG_SRC_LOCATION);

  if (color == 0) {
    strcat(nombreImagen, "blanco");
  } else {
    strcat(nombreImagen, "negro");
  }

  strcat(nombreImagen, "/");
  char pieza_str[2] = {pieza, '\0'};
  strcat(nombreImagen, pieza_str);
  strcat(nombreImagen, IMG_SRC_EXTENSION);
}

Pieza *crearPiezas(int color) {
  Pieza *piezas = (Pieza *)malloc(16 * sizeof(Pieza));
  int y = color == 0 ? 1 : 6;
  int y2 = color == 0 ? 0 : 7;
  char tipos[] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                  'T', 'T', 'C', 'C', 'A', 'A', 'Q', 'R'};
  int xs[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 7, 1, 6, 2, 5, 3, 4};
  int ys[] = {y, y, y, y, y, y, y, y, y2, y2, y2, y2, y2, y2, y2, y2};

  for (int i = 0; i < 16; i++) {
    int valor = 0;

    switch (tipos[i]) {
    case 'P':
      valor = 1;
      break;
    case 'C':
    case 'A':
      valor = 3;
      break;
    case 'T':
      valor = 5;
      break;
    case 'Q':
      valor = 9;
      break;
    case 'R':
      valor = 100;
      break;
    default:
      valor = 0;
    }

    inicializarPieza(&piezas[i], tipos[i], color, valor, xs[i], ys[i]);
  }

  return piezas;
}

Pieza *crearPiezasNegras() { return crearPiezas(0); }

Pieza *crearPiezasBlancas() { return crearPiezas(1); }

Pieza *buscarPieza(int x, int y, Pieza *piezasBlancas, Pieza *piezasNegras) {
  // Buscar la pieza en el array de piezas blancas
  for (int i = 0; i < 16; i++) {
    if (piezasBlancas[i].coordenadaX == x &&
        piezasBlancas[i].coordenadaY == y && !piezasBlancas[i].capturada) {
      return &piezasBlancas[i];
    }
  }

  // Si no se encontró la pieza en el array de piezas blancas, buscarla en el
  // array de piezas negras
  for (int i = 0; i < 16; i++) {
    if (piezasNegras[i].coordenadaX == x && piezasNegras[i].coordenadaY == y &&
        !piezasNegras[i].capturada) {
      return &piezasNegras[i];
    }
  }

  // Si no se encontró la pieza, devolver NULL
  return NULL;
}

Move *obtenerMovimientosArray(Tablero *tablero, Pieza *p, Pieza *piezasAliadas,
                              Pieza *piezasEnemigas) {
  obtenerMovimientos(tablero, p, piezasAliadas, piezasEnemigas);

  // Verificar que haya movimientos
  if (numMovimientos == 0) {
    return NULL;
  }
  // Verificar que sean movimientos validos, si no, se eliminan
  for (int i = 0; i < numMovimientos; i++) {
    if (!esMovimientoValido(posiblesMovimientos[i].x,
                            posiblesMovimientos[i].y)) {
      for (int j = i; j < numMovimientos - 1; j++) {
        posiblesMovimientos[j] = posiblesMovimientos[j + 1];
      }
      numMovimientos--;
    }
  }
  return posiblesMovimientos;
}

// Funcion que recorre 2 arrays de piezas y las coloca en el tablero
void colocarPiezasEnTablero(Tablero *tablero, Pieza *piezasBlancas,
                            Pieza *piezasNegras) {
  for (int i = 0; i < 16; i++) {
    tablero
        ->casillas[piezasBlancas[i].coordenadaX][piezasBlancas[i].coordenadaY] =
        &piezasBlancas[i];
    tablero
        ->casillas[piezasNegras[i].coordenadaX][piezasNegras[i].coordenadaY] =
        &piezasNegras[i];
  }
}

//! LEGACY
void imprimirTablero(Tablero *tablero) {
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

int esJaqueMate(Tablero *tablero, Pieza *piezasAliadas, Pieza *piezasEnemigas) {
  // Buscar al rey aliado
  Pieza *rey = NULL;
  for (int i = 0; i < 16; i++) {
    if (piezasAliadas[i].tipo == 'R' && !piezasAliadas[i].capturada) {
      rey = &piezasAliadas[i];
      break;
    }
  }

  if (rey == NULL) {
    debugMessage("No se encontró al rey aliado.\n");
    return 1; // No hay rey, está capturado, se considera jaque mate
  }

  // Verificar si el rey está en jaque
  if (Check4Checks(piezasEnemigas, tablero, piezasAliadas) == 0) {
    return 0; // El rey no está en jaque, no hay jaque mate
  }

  // Intentar mover todas las piezas aliadas
  for (int i = 0; i < 16; i++) {
    Pieza *pieza = &piezasAliadas[i];
    if (pieza->capturada) {
      continue;
    }

    // Obtener los posibles movimientos de la pieza
    obtenerMovimientos(tablero, pieza, piezasAliadas, piezasEnemigas);

    for (int j = 0; j < numMovimientos; j++) {
      // Crear copias del tablero y las piezas para simular el movimiento
      Tablero *tableroCopia = copiarTablero(tablero);
      Pieza *piezasAliadasCopia = copiarPiezas(piezasAliadas);
      Pieza *piezasEnemigasCopia = copiarPiezas(piezasEnemigas);

      Pieza *piezaCopia = buscarPieza(pieza->coordenadaX, pieza->coordenadaY,
                                      piezasAliadasCopia, piezasEnemigasCopia);

      // Mover la pieza en la copia del tablero
      int resultado = moverPieza(
          tableroCopia, piezaCopia, posiblesMovimientos[j].x,
          posiblesMovimientos[j].y, piezasAliadasCopia, piezasEnemigasCopia);

      // Verificar si el rey sigue en jaque
      if (resultado == 0 && Check4Checks(piezasEnemigasCopia, tableroCopia,
                                         piezasAliadasCopia) == 0) {
        free(tableroCopia);
        free(piezasAliadasCopia);
        free(piezasEnemigasCopia);
        return 0; // Existe un movimiento que saca al rey del jaque
      }

      free(tableroCopia);
      free(piezasAliadasCopia);
      free(piezasEnemigasCopia);
    }
  }

  // Intentar mover el rey
  obtenerMovimientos(tablero, rey, piezasAliadas, piezasEnemigas);
  for (int i = 0; i < numMovimientos; i++) {
    // Crear copias del tablero y las piezas para simular el movimiento
    Tablero *tableroCopia = copiarTablero(tablero);
    Pieza *piezasAliadasCopia = copiarPiezas(piezasAliadas);
    Pieza *piezasEnemigasCopia = copiarPiezas(piezasEnemigas);

    Pieza *reyCopia = buscarPieza(rey->coordenadaX, rey->coordenadaY,
                                  piezasAliadasCopia, piezasEnemigasCopia);

    // Mover el rey en la copia del tablero
    int resultado = moverPieza(tableroCopia, reyCopia, posiblesMovimientos[i].x,
                               posiblesMovimientos[i].y, piezasAliadasCopia,
                               piezasEnemigasCopia);

    // Verificar si el rey sigue en jaque
    if (resultado == 0 && Check4Checks(piezasEnemigasCopia, tableroCopia,
                                       piezasAliadasCopia) == 0) {
      free(tableroCopia);
      free(piezasAliadasCopia);
      free(piezasEnemigasCopia);
      return 0; // Existe un movimiento que saca al rey del jaque
    }

    free(tableroCopia);
    free(piezasAliadasCopia);
    free(piezasEnemigasCopia);
  }

  return 1; // El rey no puede escapar del jaque, es jaque mate
}

Tablero *inicializarTableroBackend() {
  Tablero *tablero = (Tablero *)malloc(sizeof(Tablero));
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      tablero->casillas[i][j] = NULL;
    }
  }
  return tablero;
}

Tablero *copiarTablero(Tablero *tablero) {
  Tablero *tableroCopia = (Tablero *)malloc(sizeof(Tablero));
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      tableroCopia->casillas[i][j] = tablero->casillas[i][j];
    }
  }
  return tableroCopia;
}

Pieza *copiarPiezas(Pieza *piezas) {
  Pieza *piezasCopia = (Pieza *)malloc(16 * sizeof(Pieza));
  for (int i = 0; i < 16; i++) {
    piezasCopia[i] = piezas[i];
  }
  return piezasCopia;
}
