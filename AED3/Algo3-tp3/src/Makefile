#Compilador que será utilizado
CC=g++

# flags de compilación
CXXFLAGS=-g -std=c++11 -O3 

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación [COMPLETAR]
INCDIR= .

# Agregar acá los archivos .cpp a compilar [COMPLETAR]

SOURCES=main.cpp ejercicio1.cpp ejercicio2.cpp ejercicio3.cpp ejercicio4.cpp Estacion.cpp


# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=tp3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CXXFLAGS) $< -c -o $@
