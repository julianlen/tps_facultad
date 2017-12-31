#Compilador que será utilizado
CC=g++

# flags de compilación
CXXFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación [COMPLETAR]
INCDIR= .

# Agregar acá los archivos .cpp a compilar [COMPLETAR]
SOURCES=main.cpp ejercicio3.cpp ejercicio2.cpp ejercicio1.cpp Estado.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=tp1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CXXFLAGS) $< -c -o $@
