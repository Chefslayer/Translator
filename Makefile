C = classes/
I = includes/
L = lib/
T = test/

SRC = $(C)Lexicon.cpp  $(I)functions.cpp $(I)output.cpp ${I}hypothesis.cpp $(C)Bleu.cpp $(C)Levenshtein.cpp
OBJ = $(SRC:%cpp=%o)

CFLAGS = -g
LDFLAGS = -lz

all: rate_translation
clean:
	-rm $(OBJ) translate rate_translation singleWordExtract hypTest.o lexiconTest.o
rebuild: clean translate rate_translation

translate: translate.cpp $(OBJ)
	$(CXX) $^ -o $@

rate_translation: rate_translation.cpp $(OBJ)
	$(CXX) $^ -o $@

singleWordExtract: singleWordExtract.cpp ${L}gzstream.C $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

hypTest: $(T)hypTest.cpp $(I)hypothesis.o
	$(CXX) $^ -o hypTest.o

lexiconTest: $(T)lexiconTest.cpp $(I)functions.o $(C)Lexicon.o
	$(CXX) $^ -o lexiconTest.o

bleuTest: $(T)bleuTest.cpp $(C)Bleu.o
	$(CXX) $^ -o bleuTest.o

%o: %cpp
	$(CXX) -c -p -o $@ $< $(CFLAGS)
