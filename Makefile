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

mybusybox.o:
	${CC} ${STD} -c mybusybox.cpp

build: ls.o mybusybox.o ln.o cp.o
	${CC} ls.o ln.o cp.o mybusybox.o -o ${EXE}
	rm *.o

link: build
	cd ./bin && ln -s ../${EXE} ls
	cd ./bin && ln -s ../${EXE} ln
	cd ./bin && ln -s ../${EXE} cp

clean:
	rm -f bin/*
	rm -f ${EXE}

