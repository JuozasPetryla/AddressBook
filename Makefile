bin/main: build/main.o build/llist.o build/node.o build/address.o build/util.o | bin
	gcc build/main.o build/llist.o build/node.o build/address.o build/util.o -o bin/main

build/main.o: main.c | build
	gcc -c main.c -o build/main.o

build/llist.o: llist.c | build
	gcc -c llist.c -o build/llist.o

build/node.o: node.c | build
	gcc -c node.c -o build/node.o

build/address.o: address.c | build
	gcc -c address.c -o build/address.o

build/util.o: util.c | build
	gcc -c util.c -o build/util.o

bin:
	mkdir -p bin

build:
	mkdir -p build