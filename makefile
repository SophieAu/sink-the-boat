# compiles to windows by default.
all: sink-the-boat.exe

linux: sink-the-boat.o
	gcc -std=c99 -pedantic -o sink-the-boat.exe main.o boat.o water.o -lGL -lGLU -lglut -lm


sink-the-boat.exe: sink-the-boat.o
	gcc -std=c99 -pedantic -o sink-the-boat.exe main.o boat.o water.o callbacks.o globalvariables.o -lopengl32 -lglu32 -lglut32win -lm

sink-the-boat.o:
	gcc -std=c99 -pedantic -c main.c water.c boat.c callbacks.c globalvariables.c
     
clean:
	rm sink-the-boat.exe main.o boat.o water.o
