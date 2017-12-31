#Compilador que será utilizado
CC=g++

# flags de compilación
CXXFLAGS=-g -std=c++11 -O3


# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación [COMPLETAR]
INCDIR= ./include/Eigen/


# Agregar acá los archivos .cpp a compilar [COMPLETAR]

SOURCES=main.cpp include/pgmLibrary.cpp include/commons.cpp


# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=tp2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I $(INCDIR) $(CXXFLAGS) $< -c -o $@
