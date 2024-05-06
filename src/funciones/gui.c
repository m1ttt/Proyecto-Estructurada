
#include "../prototipos/gui.h"

// Función generica para crear una ventana
GtkWidget *crearVentana(const char *titulo, int ancho, int alto) {
  GtkCssProvider *provider =
      gtk_css_provider_new(); // Inicializa el GtkCssProvider
  GError *error = NULL;

  GtkWidget *ventana;

  gtk_init(NULL, NULL);

  if (!gtk_css_provider_load_from_path(provider, "src/assets/estilos.css",
                                       &error)) {
    g_printerr("Error loading CSS: %s\n", error->message);
    g_error_free(error);
  } else {
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
  }
  g_object_unref(provider);

  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(ventana), titulo);
  gtk_window_set_default_size(GTK_WINDOW(ventana), ancho, alto);
  gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);

  return ventana;
}