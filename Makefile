all: Grid.o Grid.cpp main.cpp
	g++ -o main.x main.cpp Grid.o -I.
Grid.o: Grid.cpp
	g++ -c Grid.cpp -I.
clean:
	rm -f *.o *.x
