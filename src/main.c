#include <stdio.h>
#include "prototipos/funciones.h"

int main() {
    int a = 10;
    int b = 20;
    
    printf("La suma de %d y %d es %d\n", a, b, sumar(a, b));
    
    return 0;
}
