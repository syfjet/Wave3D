TARGET = wave_3d
CC = g++

CFLAGS = -Ofast -fopenmp

SOURCES = \
src/reader/construction_mesh.cpp \
src/reader/read_input_file.cpp \
src/boundary/boundary.cpp \
src/solver/geometry.cpp \
src/solver/equation.cpp \
src/solver/solver.cpp \
src/paraview/out.cpp \
src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)




