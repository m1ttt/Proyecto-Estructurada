#include <gtk-3.0/gtk/gtk.h>

// Función generica para crear una ventana
GtkWidget *crearVentana(const char *titulo, int ancho, int alto) {
  GtkWidget *ventana;

  gtk_init(NULL, NULL);

  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(ventana), titulo);
  gtk_window_set_default_size(GTK_WINDOW(ventana), ancho, alto);
  gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);

  return ventana;
}