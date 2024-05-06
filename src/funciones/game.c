#include "../prototipos/game.h"
#include "../prototipos/acciones.h"

void generacionTableroGUI() {
  GtkWidget *grid;
  GtkWidget *ventana = crearVentana("Ajedrez", 800, 800);
  GtkWidget *labelTurno;
  GtkWidget *vbox;

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

  Pieza *piezasBlancas = crearPiezasBlancas();
  Pieza *piezasNegras = crearPiezasNegras();
  Tablero *tablero = inicializarTableroBackend();
  colocarPiezasEnTablero(tablero, piezasBlancas,
                         piezasNegras); // Coloca las piezas en el tablero
  inicializarTablero(grid, piezasBlancas, piezasNegras);

  DatosCasilla *datos = malloc(sizeof(DatosCasilla));
  datos->grid = grid;
  datos->piezasBlancas = piezasBlancas;
  datos->piezasNegras = piezasNegras;
  datos->tablero = tablero;
  datos->botonSeleccionado = NULL;
  datos->turno = JUGADOR1;

  // Crear un label para mostrar el turno del jugador
  labelTurno = gtk_label_new(NULL);
  datos->labelTurno = labelTurno; // Guarda el label en los datos
  actualizarLabelTurno(labelTurno,
                       datos->turno); // Actualiza el label inicialmente
  gtk_box_pack_start(GTK_BOX(vbox), labelTurno, FALSE, FALSE, 0);

  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      GtkWidget *casilla = gtk_toggle_button_new();
      gtk_grid_attach(GTK_GRID(grid), casilla, j, i, 1, 1);
      g_signal_connect(casilla, "clicked", G_CALLBACK(on_casilla_clicked),
                       datos);
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

  gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(ventana), vbox);
  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(ventana);
  gtk_main();
}

void on_casilla_clicked(GtkWidget *casilla, gpointer data) {
  DatosCasilla *datos = (DatosCasilla *)data;
  int x, y;
  gtk_container_child_get(GTK_CONTAINER(datos->grid), casilla, "left-attach",
                          &x, "top-attach", &y, NULL);
  if (datos->botonSeleccionado != NULL && datos->botonSeleccionado != casilla) {
    if (gtk_toggle_button_get_active(
            GTK_TOGGLE_BUTTON(datos->botonSeleccionado))) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(datos->botonSeleccionado),
                                   FALSE);
      Pieza *pieza = buscarPieza(datos->x, datos->y, datos->piezasBlancas,
                                 datos->piezasNegras);
      if (pieza != NULL &&
          ((datos->turno == TURNO_BLANCO && pieza->color == 0) ||
           (datos->turno == TURNO_NEGRO && pieza->color == 1))) {
        int resultado = moverPieza(datos->tablero, pieza, x, y,
                                   datos->piezasBlancas, datos->piezasNegras);
        if (resultado == 0) { // Si la pieza se movió
          // Quitar la imagen de la casilla anterior
          GtkWidget *casillaAnterior =
              gtk_grid_get_child_at(GTK_GRID(datos->grid), datos->x, datos->y);
          gtk_button_set_image(GTK_BUTTON(casillaAnterior), NULL);

          datos->turno =
              (datos->turno == TURNO_BLANCO) ? TURNO_NEGRO : TURNO_BLANCO;
          debugMessage("El turno actual es %s\n",
                       datos->turno == TURNO_BLANCO ? "BLANCO" : "NEGRO");
          actualizarPosiciones(datos);
          actualizarLabelTurno(datos->labelTurno, datos->turno);
        }
      }
    }
  }
  datos->botonSeleccionado = casilla;
  datos->x = x;
  datos->y = y;
  Pieza *pieza = buscarPieza(x, y, datos->piezasBlancas, datos->piezasNegras);
  if (pieza != NULL) {
    if ((datos->turno == TURNO_BLANCO && pieza->color == 0) ||
        (datos->turno == TURNO_NEGRO && pieza->color == 1)) {
      desplegarMovimientosGUI(GTK_WIDGET(datos->grid), x, y, pieza,
                              datos->piezasBlancas, datos->piezasNegras,
                              datos->tablero);
    }
  }
}

void button_toggled(GtkToggleButton *button, gpointer user_data) {
  GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(button));

  if (gtk_toggle_button_get_active(button)) {
    gtk_style_context_remove_class(context, "movimiento-posible");
    g_object_set_data(G_OBJECT(button), "active", GINT_TO_POINTER(0));
  } else {
    gtk_style_context_add_class(context, "movimiento-posible");
    g_object_set_data(G_OBJECT(button), "active", GINT_TO_POINTER(1));
  }

  gtk_widget_queue_draw(GTK_WIDGET(button));
}
void desplegarMovimientosGUI(GtkWidget *grid, int x, int y, Pieza *pieza,
                             Pieza *piezasBlancas, Pieza *piezasNegras,
                             Tablero *tablero) {
  GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(grid), x, y);
  if (pieza != NULL) {
    debugMessage("Pieza: Tipo=%c, Color=%s, Coordenada=(%d, %d), Capturada=%s",
                 pieza->tipo, pieza->color ? "B" : "N", pieza->coordenadaX,
                 pieza->coordenadaY, pieza->capturada ? "Sí" : "No");

    Move *movimientos = g_object_get_data(G_OBJECT(button), "movimientos");

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {
      if (movimientos == NULL) {
        movimientos = obtenerMovimientosArray(tablero, pieza, piezasBlancas,
                                              piezasNegras);

        for (int i = 0; i < numMovimientos; i++) {
          debugMessage("Movimiento %d: (%d, %d)", i, movimientos[i].x,
                       movimientos[i].y);

          button = gtk_grid_get_child_at(GTK_GRID(grid), movimientos[i].x,
                                         movimientos[i].y);

          GtkStyleContext *context = gtk_widget_get_style_context(button);

          gtk_style_context_add_class(context, "movimiento-posible");

          g_object_set_data(G_OBJECT(button), "active", GINT_TO_POINTER(1));

          g_signal_connect(button, "toggled", G_CALLBACK(button_toggled),
                           movimientos);

          gtk_widget_queue_draw(button);
        }

        // Almacenar los movimientos posibles en el botón original
        g_object_set_data(G_OBJECT(button), "movimientos", movimientos);
      }
    } else if (movimientos != NULL) {
      // Si el botón está deseleccionado, eliminar la clase "movimiento-posible"
      for (int i = 0; i < numMovimientos; i++) {
        button = gtk_grid_get_child_at(GTK_GRID(grid), movimientos[i].x,
                                       movimientos[i].y);
        GtkStyleContext *context = gtk_widget_get_style_context(button);
        gtk_style_context_remove_class(context, "movimiento-posible");
        gtk_widget_queue_draw(button);
      }

      // Restablecer el estado del botón original
      g_object_set_data(G_OBJECT(button), "active", GINT_TO_POINTER(0));
      // Eliminar los movimientos almacenados
      g_object_set_data(G_OBJECT(button), "movimientos", NULL);
    }
  } else {
    debugMessage("No hay ninguna pieza en la casilla (%d, %d)", x, y);
  }

  // Aquí puedes usar piezasBlancas y piezasNegras como necesites
}

void actualizarLabelTurno(GtkWidget *labelTurno, int turno) {
  gchar *texto;
  if (turno == JUGADOR1) {
    texto =
        g_strdup("<span font='20' weight='bold'>Turno del Jugador 1</span>");
  } else {
    texto =
        g_strdup("<span font='20' weight='bold'>Turno del Jugador 2</span>");
  }
  gtk_label_set_markup(GTK_LABEL(labelTurno), texto);
  g_free(texto);

  // Añadir padding y poner el texto en negritas
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(
      provider, "* { padding: 10px; font-weight: bold; }", -1, NULL);
  GtkStyleContext *context = gtk_widget_get_style_context(labelTurno);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_object_unref(provider);
}
void actualizarPosiciones(DatosCasilla *datos) {

  // Actualizar las posiciones de las piezas blancas y negras
  for (int color = 0; color <= 1; color++) { // 0 para blancas, 1 para negras
    Pieza *piezas = (color == 0) ? datos->piezasBlancas : datos->piezasNegras;
    for (int i = 0; i < 16; i++) {
      if (!piezas[i].capturada) {
        int x = piezas[i].coordenadaX;
        int y = piezas[i].coordenadaY;
        GtkWidget *casilla = gtk_grid_get_child_at(GTK_GRID(datos->grid), x, y);
        if (casilla != NULL) {
          char nombre_imagen[50];
          obtenerNombreImagen(nombre_imagen, piezas[i].tipo, color);
          GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(
              nombre_imagen, IMG_GUI_WIDTH, IMG_GUI_HEIGHT, TRUE, NULL);
          GtkWidget *imagen = gtk_image_new_from_pixbuf(pixbuf);
          gtk_button_set_image(GTK_BUTTON(casilla), imagen);
        }
      }
    }
  }
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