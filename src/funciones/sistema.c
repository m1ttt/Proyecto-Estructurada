#include "../prototipos/sistema.h"

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

/**
 * Imprime un mensaje de depuración en la consola y lo escribe en un archivo de
 * registro.
 *
 * @param message El formato del mensaje de depuración, como en printf.
 * @param ... Los valores para reemplazar en el formato del mensaje.
 */

void debugMessage(char *message, ...) {
  va_list args;
  va_start(args, message);

  char formatted_message[256];
  vsnprintf(formatted_message, sizeof(formatted_message), message, args);

  va_end(args);

  time_t now = time(NULL);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

  printf("#DEBUG %s: %s\n", timestamp, formatted_message);

  struct stat st = {0};
  if (stat("src/sys", &st) == -1) {
    mkdir("src/sys", 0700);
  }

  FILE *file = fopen("src/sys/logs.txt", "a");
  if (file == NULL) {
    printf("No se pudo abrir el archivo src/sys/logs.txt\n");
    return;
  }

  fprintf(file, "#DEBUG %s: %s\n", timestamp, formatted_message);
  fclose(file);
}