# General makefile for c++ - choose PROG =   name of given program
# Here we define compiler option, libraries and the  target
CPPflags= c++ -Wall
# Here we define the library functions we nee
LIB = -larmadillo -llapack -lblas
# Here we define the name of the executable
PROG= project2
${PROG} :	   	jacobi_method.o  maxoffdiag.o rotate.o main.o
			${CPPflags} jacobi_method.o maxoffdiag.o rotate.o main.o ${LIB} -o ${PROG}

jacobi_method.o :			jacobi_method.cpp
		        	${CPPflags} -c jacobi_method.cpp

maxoffdiag.o :			maxoffdiag.cpp
		        	${CPPflags} -c maxoffdiag.cpp

rotate.o :		rotate.cpp
							${CPPflags} -c rotate.cpp

main.o :			main.cpp
							${CPPflags} -c main.cpp
