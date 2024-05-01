#include "../prototipos/sistema.h"
#include <stdio.h>
#include <stdlib.h>

// Funcion para detectar el sistema en el cual se esta corriendo.

void detectorDeSistema() {
#ifdef _WIN32
  system("cls");
  printf("Windows\n");
#elif __APPLE__
  system("clear");
  printf("Mac OS\n");

#elif __linux__
  system("clear");
  printf("Linux\n");

#elif __unix__
  system("clear");
  printf("Unix\n");

#else
  printf("Unknown\n");
#endif
}