all: copy_with_holes

copy_with_holes: copy_with_holes.o
	g++ copy_with_holes.o -o copy_with_holes

copy_with_holes.o: copy_with_holes.cpp
	g++ -c copy_with_holes.cpp

clean:
	rm -rf *.o copy_with_holes
