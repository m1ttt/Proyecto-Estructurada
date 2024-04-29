# Nombre del ejecutable
TARGET = ajedrez

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall

# Directorio de objetos y fuentes
OBJDIR = src/obj
SRCDIR = src
FUNCDIR = $(SRCDIR)/funciones
PROTODIR = $(SRCDIR)/prototipos

# Encuentra todos los archivos .c en los directorios de funciones y prototipos
SOURCES = $(wildcard $(SRCDIR)/*.c $(FUNCDIR)/*.c)
# Genera los nombres de los archivos .o correspondientes
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

# Regla principal
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Regla para construir el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

# Regla para construir los objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FUNCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
	rmdir $(OBJDIR)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)