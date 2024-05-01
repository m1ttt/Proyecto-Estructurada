# Nombre del ejecutable
TARGET = ajedrez

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -g -Wall -lncurses

# Directorio de objetos y fuentes
OBJDIR = src/obj
SRCDIR = src
FUNCDIR = $(SRCDIR)/funciones

# Encuentra todos los .c en el directorio de fuentes
SOURCES = $(wildcard $(SRCDIR)/*.c $(FUNCDIR)/*.c)

# Genera los .o a partir de los .c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

# Compilar dependiendo del sistema operativo
UNAME_S := $(shell uname -s)

# Aqui es donde se construye el ejecutable
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Construir el ejecutable
$(TARGET): $(OBJECTS)
ifeq ($(UNAME_S),Windows)
	$(CC) $(CFLAGS) -o $(TARGET).exe $^
else
	$(CC) $(CFLAGS) -o $(TARGET) $^
endif

# Construir los archivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FUNCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar .o y ejecutable
clean:
ifeq ($(UNAME_S),Windows)
	rm -f $(TARGET).exe $(OBJDIR)/*.o
else
	rm -f $(TARGET) $(OBJDIR)/*.o
endif
	rmdir $(OBJDIR)

# Ejecutar el programa
run: $(TARGET)
ifeq ($(UNAME_S),Windows)
	./$(TARGET).exe
else
	./$(TARGET)
endif