#include "../prototipos/menu.h"
#include "../prototipos/game.h"
#include "../prototipos/gui.h"
#include "../prototipos/sistema.h"
#include <menu.h>

/**
 * Inicializa el menú principal del juego.
 */

void jugar(GtkWidget *boton, gpointer ventana) {
  gtk_widget_destroy(GTK_WIDGET(ventana));
  debugMessage("Inicializando juego...");
  generacionTableroGUI();
}

/**
 * Muestra un diálogo con información sobre los creadores.
 */
void acercaDe(GtkWidget *boton, gpointer ventana_principal) {
  GtkWidget *dialogo, *label, *content_area;
  GtkDialogFlags flags;

  // Crear un nuevo diálogo modal
  flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  dialogo =
      gtk_dialog_new_with_buttons("Acerca de", GTK_WINDOW(ventana_principal),
                                  flags, "_OK", GTK_RESPONSE_NONE, NULL);
  g_signal_connect_swapped(dialogo, "response", G_CALLBACK(gtk_widget_destroy),
                           dialogo);

  // Añadir un label al área de contenido del diálogo
  content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialogo));
  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label),
                       "<span font='12'>Hecho con el &lt;3 por castores rompe "
                       "piernas :)</span>");
  gtk_container_add(GTK_CONTAINER(content_area), label);

  gtk_widget_show_all(dialogo);
}

/**
 * Cierra la aplicación.
 */
void salir() { exit(0); }

void inicializarMenu() {
  limpiezaDePantalla();
  debugMessage("Inicializando menu...");
  menu();
}
/**
 * Crea y muestra el menú principal de la aplicación.
 */
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

  const char *labels[] = {"Jugar", "Acerca de", "Salir"};
  GCallback callbacks[] = {G_CALLBACK(jugar), G_CALLBACK(acercaDe),
                           G_CALLBACK(salir)};
  for (int i = 0; i < 3; i++) {
    GtkWidget *boton = gtk_button_new_with_label(labels[i]);
    g_signal_connect(boton, "clicked", callbacks[i], ventana);
    gtk_widget_set_margin_start(boton, 50);
    gtk_widget_set_margin_end(boton, 50);
    gtk_widget_set_margin_top(boton, 10);
    gtk_widget_set_margin_bottom(boton, 50);
    gtk_box_pack_start(GTK_BOX(box), boton, TRUE, TRUE, 0);

    // Añadir estilos CSS a los botones
    GtkStyleContext *context = gtk_widget_get_style_context(boton);
    gtk_style_context_add_class(context, "boton-menu");
  }

  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(ventana);
  gtk_main();
}
/**
 * Limpia la pantalla de la terminal.
 */
void limpiezaDePantalla() {
  int i = detectorDeSistema();
  if (i == 1) {
    system("cls");
  } else {
    system("clear");
  }
}