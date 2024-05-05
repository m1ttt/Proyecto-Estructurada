#include "../prototipos/sistema.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

// Funcion para detectar el sistema en el cual se esta corriendo.
int detectorDeSistema() {
#ifdef _WIN32
  return 1;
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
  time_t now = time(NULL);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

  printf("#DEBUG %s: %s\n", timestamp, message);
  struct stat st = {0};
  if (stat("src/sys", &st) == -1) {
    mkdir("src/sys", 0700);
  }

  FILE *file = fopen("src/sys/logs.txt", "a");
  if (file == NULL) {
    printf("No se pudo abrir el archivo src/sys/logs.txt\n");
    return;
  }

  fprintf(file, "#DEBUG %s: %s\n", timestamp, message);
  fclose(file);
}