#ifndef GUI_H
#define GUI_H

#include <gtk-3.0/gtk/gtk.h>

GtkWidget *crearVentana(const char *titulo, int ancho, int alto);
void mostrarDialogo(const char *titulo, const char *mensaje, GtkWidget *casilla);

#endif