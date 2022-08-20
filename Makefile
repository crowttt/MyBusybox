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

MyBusybox.o:
	${CC} ${STD} -c MyBusybox.cpp

shell.o:
	${CC} ${STD} -c -lreadline lib/shell.cc

build: ls.o MyBusybox.o ln.o cp.o shell.o
	${CC} ls.o ln.o cp.o MyBusybox.o shell.o -lreadline -o ${EXE}
	rm *.o

link: build
	ln -s ${EXE} shell
	mkdir -p bin
	cd ./bin && ln -s ../${EXE} ls
	cd ./bin && ln -s ../${EXE} ln
	cd ./bin && ln -s ../${EXE} cp

clean:
	rm -f bin/*
	find -type l -delete
	rm -f ${EXE}



