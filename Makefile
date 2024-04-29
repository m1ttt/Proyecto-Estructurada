# Nombre del ejecutable
TARGET = main

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall

# Directorio de objetos y fuentes
OBJDIR = obj
SRCDIR = src

# Regla principal
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Regla para construir el ejecutable
$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/funciones.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJDIR)/main.o $(OBJDIR)/funciones.o

# Regla para construir los objetos
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/funciones.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/funciones.o: $(SRCDIR)/funciones.c $(SRCDIR)/funciones.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/funciones.c -o $(OBJDIR)/funciones.o

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
	rmdir $(OBJDIR)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)