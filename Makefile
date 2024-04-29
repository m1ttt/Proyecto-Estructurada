# Nombre del ejecutable
TARGET = main

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall

# Regla principal
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): main.o funciones.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o funciones.o

# Regla para construir los objetos
main.o: main.c funciones.h
	$(CC) $(CFLAGS) -c main.c

functions.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) *.o

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)
