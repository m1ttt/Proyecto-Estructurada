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

# Compilar dependiendo del sistema operativo
ifeq ($(OS),Windows_NT)
UNAME_S := Windows
else
UNAME_S := $(shell uname -s)
endif

# Aqui es donde se construye el ejecutable
all: check_gtk $(OBJDIR) $(TARGET)

check_gtk:
ifeq ($(UNAME_S),Windows)
	@echo Verificando la instalacion de GTK...
	@if not exist C:\msys64\mingw64\bin\gtk3-demo.exe ( \
		echo GTK no esta instalado. Instalando... & \
		call install-gtk.bat \
	)
endif

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Construir el ejecutable
$(TARGET): $(OBJECTS)
ifeq ($(UNAME_S),Windows)
	$(CC) $(CFLAGS) -o $(TARGET).exe $^ $(LDFLAGS)
else
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)
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
