#include "../prototipos/menu.h"
#include "../prototipos/sistema.h"
#include <gtk-3.0/gtk/gtk.h>
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
  limpiezaDePantalla();
  printf("Jugando...\n");
  GtkWidget *ventana;
  GtkWidget *grid;
  int i, j;

  gtk_init(NULL, NULL);

  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(ventana), "Ajedrez");
  gtk_window_set_default_size(GTK_WINDOW(ventana), 800, 800);

  grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      GtkWidget *casilla = gtk_button_new();
      gtk_grid_attach(GTK_GRID(grid), casilla, j, i, 1, 1);
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
  GtkWidget *ventana;
  GtkWidget *box;
  GtkWidget *boton_jugar;
  GtkWidget *boton_salir;
  GtkWidget *titulo;

  gtk_init(NULL, NULL);

  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(ventana), "Ajedrez");
  gtk_window_set_default_size(GTK_WINDOW(ventana), 400, 400);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(ventana), box);

  titulo = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(titulo),
                       "<span font='24' weight='bold'>Ajedrez</span>");
  gtk_box_pack_start(GTK_BOX(box), titulo, TRUE, TRUE, 0);

  boton_jugar = gtk_button_new_with_label("Jugar");
  g_signal_connect(boton_jugar, "clicked", G_CALLBACK(jugar), NULL);
  gtk_widget_set_margin_start(boton_jugar, 50);
  gtk_widget_set_margin_end(boton_jugar, 50);
  gtk_widget_set_margin_top(boton_jugar, 10);
  gtk_widget_set_margin_bottom(boton_jugar, 10);
  gtk_box_pack_start(GTK_BOX(box), boton_jugar, TRUE, TRUE, 0);

  boton_salir = gtk_button_new_with_label("Salir");
  g_signal_connect(boton_salir, "clicked", G_CALLBACK(salir), NULL);
  gtk_widget_set_margin_start(boton_salir, 50);
  gtk_widget_set_margin_end(boton_salir, 50);
  gtk_widget_set_margin_top(boton_salir, 10);
  gtk_widget_set_margin_bottom(boton_salir, 50);
  gtk_box_pack_start(GTK_BOX(box), boton_salir, TRUE, TRUE, 0);

  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(ventana);

  gtk_main();
}

void limpiezaDePantalla() {
  int sistema = detectorDeSistema();
  if (sistema == 1) {
    system("cls");
  } else {
    system("clear");
  }
}