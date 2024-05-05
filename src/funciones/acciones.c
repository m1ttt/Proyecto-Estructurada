#define IMG_GUI_HEIGHT 80
#define IMG_GUI_WIDTH 80
#define IMG_SRC_LOCATION "src/assets/piezas/"
#define IMG_SRC_EXTENSION ".png"

#include "../prototipos/acciones.h"
#include "../prototipos/materiales.h"
#include "../prototipos/sistema.h"

Move posiblesMovimientos[MAX_MOVES]; // Definición real
int numMovimientos = 0;              // Inicialización

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
  if (p->capturada) {
    printf("La pieza %c ya fue capturada.\n", p->tipo);
    return;
  }
  if (Check4Checks(piezasEnemigas, tablero, piezasAliadas) == 1 &&
      p->tipo != 'R') {
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

void calcularMovimientosSinCheck(Tablero *tablero, Pieza *p) {
  // Verifica que la pieza no haya sido capturada
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
  obtenerMovimientos(tablero, pieza, piezasAliadas,
                     piezasEnemigas); // Corrige el paso de argumentos
  if (pieza->capturada) {
    printf("La pieza %c ya fue capturada.\n", pieza->tipo);
    return 1;
  }
  if (esMovimientoValido(newX, newY)) {
    // Revisar si el rey entrara en jaque
    if (pieza->tipo == 'R') {
      for (int i = 0; i < 16; i++) {
        if (piezasEnemigas[i].capturada == 0) {
          calcularMovimientosSinCheck(tablero, &piezasEnemigas[i]);
          for (int j = 0; j < numMovimientos; j++) {
            if (posiblesMovimientos[j].x == newX &&
                posiblesMovimientos[j].y == newY) {
              printf("El rey no puede moverse a (%d, %d) porque entraria en "
                     "jaque.\n",
                     newX, newY);
              return 1;
            }
          }
        }
      }
    } 
    
    else if(pieza->tipo != 'R'){
      //Guardar las coordenadas actuales de la pieza
      int x = pieza->coordenadaX;
      int y = pieza->coordenadaY;
      //Mover la pieza
      tablero->casillas[x][y] = NULL;
      pieza->coordenadaX = newX;
      pieza->coordenadaY = newY;
      tablero->casillas[newX][newY] = pieza;
      //Verificar si el rey entra en jaque
      if(Check4Checks(piezasEnemigas, tablero, piezasAliadas) == 1){
        //Si entra en jaque, deshacer el movimiento
        tablero->casillas[newX][newY] = NULL;
        pieza->coordenadaX = x;
        pieza->coordenadaY = y;
        tablero->casillas[x][y] = pieza;
        printf("El rey no puede moverse a (%d, %d) porque entraria en jaque.\n", newX, newY);
        return 1;
      }

    }
    else if (tablero->casillas[newX][newY] != NULL &&
             tablero->casillas[newX][newY]->tipo == 'R') {
      printf("El rey no puede ser capturado.\n");
      return 1;
    }
    else if(pieza-> tipo == 'P'){
      if(newY == 0 || newY == 7){
        pieza->tipo = 'Q';
        //pieza->valor = 9; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //Mover la pieza
        tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] = NULL;
        pieza->coordenadaX = newX;
        pieza->coordenadaY = newY;
        tablero->casillas[newX][newY] = pieza;
        //Ver el color de la pieza
        if(pieza->color == 0){
          //Actualizar la imagen de la pieza
          char nombre_imagen[50];
          obtenerNombreImagen(nombre_imagen, 'Q', 0);
          GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
          pieza->imagen = pixbuf;
        }
        else{
          //Actualizar la imagen de la pieza
          char nombre_imagen[50];
          obtenerNombreImagen(nombre_imagen, 'Q', 1);
          GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
          pieza->imagen = pixbuf;
        }
      }
    }
    else if (tablero->casillas[newX][newY] ==
               NULL) { // Verifica que la casilla destino esté vacía
      tablero->casillas[pieza->coordenadaX][pieza->coordenadaY] =
          NULL;                  // Limpia la casilla actual
      pieza->coordenadaX = newX; // Actualiza la posición de la pieza
      pieza->coordenadaY = newY;
      tablero->casillas[newX][newY] =
          pieza; // Coloca la pieza en la nueva posición
      printf("Pieza movida a (%d, %d).\n", newX, newY);
      return 0;

    } else if (tablero->casillas[newX][newY]->color != pieza->color) {
      // Aquí puedes agregar lógica para manejar la captura de una pieza enemiga
      printf("Pieza capturada en (%d, %d).\n", newX, newY);
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

    else {
      printf("La casilla destino (%d, %d) está ocupada por una pieza amiga.\n",
             newX, newY);
      return 1;
    }
  } else {
    printf("Movimiento no válido para la pieza %c.\n", pieza->tipo);
    return 1;
  }
  return 0;
}
void inicializarPieza(Pieza *pieza, char tipo, int color, int x, int y) {
  pieza->tipo = tipo;
  pieza->color = color;
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
    inicializarPieza(&piezas[i], tipos[i], color, xs[i], ys[i]);
  }

  return piezas;
}




Pieza *crearPiezasNegras() { return crearPiezas(0); }

Pieza *crearPiezasBlancas() { return crearPiezas(1); }

void generacionTableroGUI() {
  GtkWidget *grid;
  GtkWidget *ventana = crearVentana("Ajedrez", 800, 800);

  grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

  Pieza *piezasBlancas = crearPiezasBlancas();
  Pieza *piezasNegras = crearPiezasNegras();
  inicializarTablero(grid, piezasBlancas, piezasNegras);

  DatosCasilla datos;
  datos.grid = grid;
  datos.piezasBlancas = piezasBlancas;
  datos.piezasNegras = piezasNegras;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      GtkWidget *casilla = gtk_toggle_button_new();
      gtk_grid_attach(GTK_GRID(grid), casilla, j, i, 1, 1);
      g_signal_connect(casilla, "clicked", G_CALLBACK(on_casilla_clicked),
                       &datos);
      // Agrega la clase "casilla-blanca" o "casilla-negra" dependiendo de la
      // posición
      if ((i + j) % 2 == 0) {
        gtk_style_context_add_class(gtk_widget_get_style_context(casilla),
                                    "casilla-blanca");
      } else {
        gtk_style_context_add_class(gtk_widget_get_style_context(casilla),
                                    "casilla-negra");
      }
    }
  }

  gtk_container_add(GTK_CONTAINER(ventana), grid);
  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(ventana);
  gtk_main();
}

void inicializarTablero(GtkWidget *grid, Pieza *piezasBlancas,
                        Pieza *piezasNegras) {
  // Inicializar todas las casillas a NULL
  GtkWidget *casilla;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      casilla = gtk_image_new();
      gtk_grid_attach(GTK_GRID(grid), casilla, j, 7 - i, 1, 1);
    }
  }

  // Colocar las piezas blancas en el tablero e imprimir sus posiciones
  for (int i = 0; i < 16; i++) {
    casilla =
        gtk_grid_get_child_at(GTK_GRID(grid), piezasBlancas[i].coordenadaX,
                              7 - piezasBlancas[i].coordenadaY);
    gtk_image_set_from_pixbuf(GTK_IMAGE(casilla), piezasBlancas[i].imagen);
    debugMessage("Pieza blanca asignada en la posición X: %d, Y: %d",
                 piezasBlancas[i].coordenadaX, piezasBlancas[i].coordenadaY);
  }

  // Colocar las piezas negras en el tablero e imprimir sus posiciones
  for (int i = 0; i < 16; i++) {
    casilla = gtk_grid_get_child_at(GTK_GRID(grid), piezasNegras[i].coordenadaX,
                                    7 - piezasNegras[i].coordenadaY);
    gtk_image_set_from_pixbuf(GTK_IMAGE(casilla), piezasNegras[i].imagen);
    debugMessage("Pieza negra asignada en la posición X: %d, Y: %d",
                 piezasNegras[i].coordenadaX, piezasNegras[i].coordenadaY);
  }
}
void on_casilla_clicked(GtkWidget *casilla, gpointer data) {
  DatosCasilla *datos = (DatosCasilla *)data;
  int x, y;
  gtk_container_child_get(GTK_CONTAINER(datos->grid), casilla, "left-attach",
                          &x, "top-attach", &y, NULL);
  Pieza *pieza = buscarPieza(x, y, datos->piezasBlancas, datos->piezasNegras);
  if (pieza != NULL) {
    desplegarMovimientosGUI(GTK_WIDGET(datos->grid), x, y, pieza);
  }
}

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

void desplegarMovimientosGUI(GtkWidget *grid, int x, int y, Pieza *pieza) {
  // Si se encontró la pieza, imprimir su información
  if (pieza != NULL) {
    debugMessage("Pieza: Tipo=%c, Color=%s, Coordenada=(%d, %d), 
                 Capturada = % s ",
                               pieza->tipo,
                 pieza->color ? "B" : "N", pieza->coordenadaX,
                 pieza->coordenadaY, pieza->capturada ? "Sí" : "No");
  } else {
    debugMessage("No hay ninguna pieza en la casilla (%d, %d)", x, y);
  }
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

//Funcion que recorre 2 arrays de piezas y las coloca en el tablero
void colocarPiezasEnTablero(Tablero *tablero, Pieza *piezasBlancas, Pieza *piezasNegras){
  for(int i = 0; i < 16; i++){
    tablero->casillas[piezasBlancas[i].coordenadaX][piezasBlancas[i].coordenadaY] = &piezasBlancas[i];
    tablero->casillas[piezasNegras[i].coordenadaX][piezasNegras[i].coordenadaY] = &piezasNegras[i];
  }
}

//! LEGACY
// void imprimirTablero(Tablero *tablero) {
//   for (int i = 0; i < 8; i++) {
//     for (int j = 0; j < 8; j++) {
//       if (tablero->casillas[j][i] == NULL) {
//         printf(". ");
//       } else {
//         printf("%c ", tablero->casillas[j][i]->tipo);
//       }
//     }
//     printf("\n");
//   }
// }
