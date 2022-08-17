SHELL = /bin/bash
CC = g++
STD = -std=c++17
CFLAGS = -g --static
BIN = bin/
SRC = $(wildcard *.cpp)
EXE = $(patsubst %.cpp,%, $(SRC))

all: clean link

ls.o:
	${CC} ${STD} -c lib/ls.cc

ln.o:
	${CC} ${STD} -c lib/ln.cc

cp.o:
	${CC} ${STD} -c lib/cp.cc

lazybox.o:
	${CC} ${STD} -c MyBusybox.cpp

build: ls.o lazybox.o ln.o cp.o
	${CC} ls.o ln.o cp.o MyBusybox.o -o ${EXE}
	rm *.o

link: build

	mkdir -p bin
	cd ./bin && ln -s ../${EXE} ls
	cd ./bin && ln -s ../${EXE} ln
	cd ./bin && ln -s ../${EXE} cp

clean:
	rm -f bin/*
	rm -f ${EXE}

