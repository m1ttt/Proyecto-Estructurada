
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

  void mostrarDialogo(const char *titulo, const char *mensaje, GtkWidget *casilla) {
    GtkWidget *dialogo, *label, *content_area;
    GtkDialogFlags flags;

    // Crear un nuevo diálogo modal
    flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialogo = gtk_dialog_new_with_buttons(titulo, GTK_WINDOW(casilla),
                                          flags, "_OK", GTK_RESPONSE_NONE, NULL);
    g_signal_connect_swapped(dialogo, "response", G_CALLBACK(gtk_widget_destroy), dialogo);

    // Añadir un label al área de contenido del diálogo
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialogo));
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), mensaje);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialogo);
  }