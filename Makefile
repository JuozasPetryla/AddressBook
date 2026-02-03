bin/main: build/main.o build/llist.o build/node.o | bin
	gcc build/main.o build/llist.o build/node.o -o bin/main

build/main.o: main.c | build
	gcc -c main.c -o build/main.o

build/llist.o: llist.c | build
	gcc -c llist.c -o build/llist.o

build/node.o: node.c | build
	gcc -c node.c -o build/node.o

bin:
	mkdir -p bin

build:
	mkdir -p build