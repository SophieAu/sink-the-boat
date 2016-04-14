all: sink-the-boat.exe

sink-the-boat.exe: sink-the-boat.o
	gcc -std=c99 -o sink-the-boat.exe main.o boat.o water.o -lopengl32 -lglu32 -lglut32win -lm

sink-the-boat.o: sink-the-boat.c
	gcc -std=c99 -c main.c water.c boat.c
     
clean:
	rm sink-the-boat.exe main.o boat.o water.o