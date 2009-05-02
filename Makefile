# richtigen relH
# v vectoren
# map von map
# makefile
# v anders einlesen
# string split

LDFLAGS  = -lz
CCFLAGS = -g
OBJ = singleWordExtract.o gzstream.o functions.o Lexicon.o
all: singleWordExtract
singleWordExtract: ${OBJ}
	g++ ${LDFLAGS} ${OBJ} -o singleWordExtract
singleWordExtract.o: singleWordExtract.cpp gzstream.h
	g++ ${CCFLAGS} -c singleWordExtract.cpp
gzstream.o: gzstream.cpp gzstream.h
	g++ ${CCFLAGS} -c gzstream.cpp
functions.o: functions.cpp functions.h
	g++ ${CCFLAGS} -c functions.cpp
Lexicon.o: Lexicon.cpp Lexicon.h
	g++ ${CCFLAGS} -c Lexicon.cpp

clean:
	rm ${OBJ} singleWordExtract

# test: test.o Lexicon.o
