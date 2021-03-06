all: Grid.o Grid.cpp main.cpp

	g++ -o main.x main.cpp Grid.o -I/usr/include/ -I. -lnetcdf_c++
Grid.o: Grid.cpp
	g++ -c Grid.cpp -I.
clean:
	rm -f *.o *.x
	rm -f ./eta/*
	rm -f ./png/*
debug:
	g++ -c -g Grid.cpp -I. 
	g++ -o -g main.x main.cpp Grid.o -I/usr/include/ -I. -lnetcdf_c++
