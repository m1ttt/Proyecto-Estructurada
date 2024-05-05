# Nombre del ejecutable
TARGET = ajedrez

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall $(shell pkg-config --cflags gtk+-3.0)

# Opciones de enlace
LDFLAGS = $(shell pkg-config --libs gtk+-3.0) -lncurses

# Directorio de objetos y fuentes
OBJDIR = src/obj
SRCDIR = src
FUNCDIR = $(SRCDIR)/funciones

# Encuentra todos los .c en el directorio de fuentes
SOURCES = $(wildcard $(SRCDIR)/*.c $(FUNCDIR)/*.c)

# Genera los .o a partir de los .c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

# Aqui es donde se construye el ejecutable
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Construir el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

# Construir los archivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FUNCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar .o y ejecutable
clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
	rmdir $(OBJDIR)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)