#ifndef SISTEMA_H
#define SISTEMA_H
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "menu.h"

// Menu principal
int detectorDeSistema();
void debugMessage(char *message, ...);

#endif