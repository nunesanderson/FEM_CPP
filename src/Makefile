CXX = g++
CXXFLAGS =-g -std=c++11 -march=native
LDLIBS = -lgsl -lgslcblas
IDIR2 =$(shell pwd)
IDIR =${shell dirname ${IDIR2}}


INCLUDES = ${IDIR}/include  
 
CFLAGS = -I$(INCLUDES)


all: main

#Link
main: main.o Messages.o Matrix.o ShapeFunctions.o
	${CXX} -o main main.o Messages.o Matrix.o ShapeFunctions.o ${LDLIBS}

#Compilation
main.o: main.cpp
	${CXX} ${CXXFLAGS} $(CFLAGS) -c -o main.o main.cpp 

Messages.o: Messages.cpp
	${CXX} ${CXXFLAGS} $(CFLAGS) -c -o Messages.o Messages.cpp

Matrix.o: Matrix.cpp
	${CXX} ${CXXFLAGS} $(CFLAGS) -c -o Matrix.o Matrix.cpp

ShapeFunctions.o: ShapeFunctions.cpp
	${CXX} ${CXXFLAGS} $(CFLAGS) -c -o ShapeFunctions.o ShapeFunctions.cpp

#Clear the directory
clean:
	rm -v *.o main
