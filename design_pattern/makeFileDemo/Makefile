objects = main.o a.o
main:$(objects)
	g++  -o main $(objects)
main.o:main.cpp
	g++  -c main.cpp 
a.o:a.h a.cpp 
	g++ -c a.cpp 
clean:
	rm -rf *.o main
