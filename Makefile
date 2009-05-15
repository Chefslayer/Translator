C = classes/
I = includes/
L = lib/
T = test/

SRC = translate.cpp ${L}gzstream.cpp ${I}functions.cpp ${C}Lexicon.cpp ${I}hypothesis.cpp
OBJ = $(SRC:%cpp=%o)

CFLAGS = -g
LDFLAGS = -lz

all: translate
clean:
	-rm $(OBJ) translate hyptest.o
rebuild: clean translate

#singleWordExtract: $(OBJ)
#	$(CXX) $^ -o $@ $(LDFLAGS)

translate: $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

hypTest: $(T)hypTest.cpp $(I)hypothesis.o
	$(CXX) $^ -o hypTest.o

lexiconTest: $(T)lexiconTest.cpp $(C)Lexicon.o
	$(CXX) $^ -o lexiconTest.o


%o: %cpp
	$(CXX) -c -p -o $@ $< $(CFLAGS)
