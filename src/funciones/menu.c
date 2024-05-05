#include "../prototipos/menu.h"
#include "../prototipos/gui.h"
#include "../prototipos/sistema.h"
#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/*NOTA:
Cada pieza define su tipo con una char, siendo:
P: Peón
R: Rey
Q: Reina
T: Torre
A: Alfil
C: Caballo
// Crear algunas piezas
    Pieza peonBlanco = {1, 1, 1, 'P', 0, 0}; // CoordenadaX, CoordenadaY, valor,
tipo, color, capturada Pieza torreNegra =   {1, 6, 5, 'T', 1, 0}; //
CoordenadaX, CoordenadaY, valor, tipo, color, capturada
*/
void jugar() {
  debugMessage("Inicializando juego...");
  GtkWidget *grid;
  GtkWidget *ventana = crearVentana("Ajedrez", 800, 800);

  grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      GtkWidget *casilla = gtk_toggle_button_new();
      gtk_grid_attach(GTK_GRID(grid), casilla, j, i, 1, 1);

      // Agrega la clase "casilla-blanca" o "casilla-negra" dependiendo de la
      // posición
      if ((i + j) % 2 == 0) {
        gtk_style_context_add_class(gtk_widget_get_style_context(casilla),
                                    "casilla-blanca");
      } else {
        gtk_style_context_add_class(gtk_widget_get_style_context(casilla),
                                    "casilla-negra");
      }

      // Agrega una imagen a la casilla
      GdkPixbuf *pixbuf =
          gdk_pixbuf_new_from_file("src/assets/amogus.jpg", NULL);
      GdkPixbuf *scaled_pixbuf =
          gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);
      GtkWidget *imagen = gtk_image_new_from_pixbuf(scaled_pixbuf);
      gtk_button_set_image(GTK_BUTTON(casilla), imagen);
    }
  }
  gtk_container_add(GTK_CONTAINER(ventana), grid);
  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(ventana);
  gtk_main();
}

void salir() { exit(0); }

OpcionesMenu opciones[] = {{"Jugar", jugar}, {"Salir", salir}};

void inicializarMenu() {
  limpiezaDePantalla();
  debugMessage("Inicializando menu...");
  menu();
}

void menu() {
  GtkWidget *box;
  GtkWidget *titulo;
  GtkWidget *ventana = crearVentana("Ajedrez", 400, 400);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(ventana), box);

  titulo = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(titulo),
                       "<span font='32' weight='bold'>Ajedrez</span>");
  gtk_box_pack_start(GTK_BOX(box), titulo, TRUE, TRUE, 0);

  const char *labels[] = {"Jugar", "Salir"};
  GCallback callbacks[] = {G_CALLBACK(jugar), G_CALLBACK(salir)};
  for (int i = 0; i < 2; i++) {
    GtkWidget *boton = gtk_button_new_with_label(labels[i]);
    g_signal_connect(boton, "clicked", callbacks[i], NULL);
    gtk_widget_set_margin_start(boton, 50);
    gtk_widget_set_margin_end(boton, 50);
    gtk_widget_set_margin_top(boton, 10);
    gtk_widget_set_margin_bottom(boton, 50);
    gtk_box_pack_start(GTK_BOX(box), boton, TRUE, TRUE, 0);
  }

  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(ventana);
  gtk_main();
}

void limpiezaDePantalla() {
  int i = detectorDeSistema();
  if (i == 1) {
    system("cls");
  } else {
    system("clear");
  }
}