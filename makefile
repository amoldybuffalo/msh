all: build

build:
	gcc main.c io.c utils.c parse.c hash_map.c builtins.c -o main -g -Wall -Wpedantic -std=gnu11 
run: build
	./main
