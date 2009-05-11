C = classes/
I = includes/
L = lib/

SRC = main.cpp ${L}gzstream.cpp ${I}functions.cpp ${C}Lexicon.cpp ${I}hypothesis.cpp
OBJ = $(SRC:%cpp=%o)

CFLAGS = -g
LDFLAGS = -lz

all: main
clean:
	-rm $(OBJ) main
rebuild: clean main

main: $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%o: %cpp
	$(CXX) -c -p -o $@ $< $(CFLAGS)
