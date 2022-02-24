# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = g++                        # compiler to use


all: find

find: find.o lib_file.a
	@echo "Creating binary"
	${CC} -o find find.o -L. -l_file -lpthread

lib_file.a: file.o
	@echo "Creating library"
	ar rcs lib_file.a file.o

file.o: file.cpp
	@echo "Creating object.."
	${CC} -c file.cpp -o file.o

find.o: find.cpp
	@echo "Creating object.."
	${CC} -c find.cpp -o find.o  

clean:
	@echo "Cleaning up..."
	rm -rvf *.o find

