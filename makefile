TARGET = wave_3d
CC = g++

CFLAGS = -Ofast -fopenmp

SOURCES = \
src/construction_mesh.cpp \
src/geometry.cpp \
src/read_input_file.cpp \
src/boundary.cpp \
src/equation.cpp \
src/solver.cpp \
src/out.cpp \
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




