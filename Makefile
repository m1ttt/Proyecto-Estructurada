# Nombre del ejecutable
TARGET = ajedrez

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall

# Directorio de objetos y fuentes
OBJDIR = src/obj
SRCDIR = src
FUNCDIR = $(SRCDIR)/functions
PROTODIR = $(SRCDIR)/prototypes

# Regla principal
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Regla para construir el ejecutable
$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/funciones.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJDIR)/main.o $(OBJDIR)/funciones.o

# Regla para construir los objetos
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(PROTODIR)/funciones.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/funciones.o: $(FUNCDIR)/funciones.c $(PROTODIR)/funciones.h
	$(CC) $(CFLAGS) -c $(FUNCDIR)/funciones.c -o $(OBJDIR)/funciones.o

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
	rmdir $(OBJDIR)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)