C = classes/
I = includes/
L = lib/
T = test/

SRC = ${L}gzstream.cpp ${I}functions.cpp ${C}Lexicon.cpp ${I}hypothesis.cpp $(C)Bleu.cpp $(C)Levenshtein.cpp
OBJ = $(SRC:%cpp=%o)

CFLAGS = -g
LDFLAGS = -lz

all: translate rate_translation
clean:
	-rm $(OBJ) translate rate_translation singleWordExtract hypTest.o lexiconTest.o
rebuild: clean translate rate_translation

translate: translate.cpp $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

rate_translation: rate_translation.cpp ${I}functions.o ${C}Lexicon.o $(C)Bleu.o $(C)Levenshtein.o
	$(CXX) $^ -o $@ $(LDFLAGS)

#kompiliert nicht weiss aber nicht warum
singleWordExtract: singleWordExtract.cpp $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

hypTest: $(T)hypTest.cpp $(I)hypothesis.o
	$(CXX) $^ -o hypTest.o

lexiconTest: $(T)lexiconTest.cpp $(C)Lexicon.o
	$(CXX) $^ -o lexiconTest.o


%o: %cpp
	$(CXX) -c -p -o $@ $< $(CFLAGS)
