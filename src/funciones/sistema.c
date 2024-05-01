#include "../prototipos/sistema.h"
#include <stdio.h>


// Funcion para detectar el sistema en el cual se esta corriendo.
int detectorDeSistema() {
#ifdef _WIN32
  reutrn 1;
#elif __APPLE__
  return 0;

#elif __linux__
  return 0;

#elif __unix__
  return 0;

#else
  printf("No reconocido :(")
#endif
}

void debugMessage(char *message) {
  printf("#DEBUG: %s\n", message);
}