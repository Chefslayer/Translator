C = classes/
I = includes/
L = lib/

SRC =translate.cpp  ${L}gzstream.cpp ${I}functions.cpp ${C}Lexicon.cpp ${I}hypothesis.cpp
OBJ = $(SRC:%cpp=%o)

CFLAGS = -g
LDFLAGS = -lz

all: translate
clean:
	-rm $(OBJ) translate
rebuild: clean translate

#singleWordExtract: $(OBJ)
#	$(CXX) $^ -o $@ $(LDFLAGS)

translate: $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%o: %cpp
	$(CXX) -c -p -o $@ $< $(CFLAGS)
