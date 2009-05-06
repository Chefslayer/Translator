LDFLAGS  = -lz
CCFLAGS = -g
PROFILE = -pg
#OBJ = singleWordExtract.o gzstream.o functions.o Lexicon.o
OBJ = gzstream.o functions.o Lexicon.o
C = classes/
I = includes/
L = lib/
all: main

main:	${OBJ} main.cpp
	g++ ${LDFLAGS} ${CCFLAGS} ${OBJ} main.cpp -o main ${PROFILE}
#singleWordExtract: ${OBJ}
#	g++ ${LDFLAGS} ${OBJ} -o singleWordExtract ${PROFILE}
#singleWordExtract.o: singleWordExtract.cpp ${L}gzstream.h
#	g++ ${CCFLAGS} -c singleWordExtract.cpp ${PROFILE}
gzstream.o: ${L}gzstream.C ${L}gzstream.h
	g++ ${CCFLAGS} -c ${L}gzstream.C
functions.o: ${I}functions.cpp ${I}functions.h
	g++ ${CCFLAGS} -c ${I}functions.cpp
Lexicon.o: ${C}Lexicon.cpp ${C}Lexicon.h
	g++ ${CCFLAGS} -c ${C}Lexicon.cpp


clean:
#	rm ${OBJ} singleWordExtract
	rm ${OBJ} main
