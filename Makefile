all: main

main: main.o solarsystem.o
	g++ -o main main.o solarsystem.o -L src/lib -lmingw32 -mwindows -lSDL2main -lSDL2

main.o: main.cpp solarsystem.h
	g++ -I src/include -c -o main.o main.cpp

solarsystem.o: solarsystem.cpp solarsystem.h
	g++ -I src/include -c -o solarsystem.o solarsystem.cpp

clean:
	rm -f main main.o solarsystem.o