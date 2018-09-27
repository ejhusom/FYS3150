# MAKEFILE
# Compiler
CPP = c++
# Flags
CPPflags = -Wall
# Include files
INCLUDES = -I../include
# Source files
SRC = hellomake.cpp hellofunc.cpp
# Object files
OBJ = $(SRC:.c=.o)
# LIibraries
LIB =
# Executable
PROG = project3.x
#====================================

all:	$(PROG)
			@echo project3.x compiled

$(PROG):	$(OBJ)
					$(CPP) $(CPPflags) $(INCLUDES) -o $(PROG) $(OBJ) $(LIB)

.c.o:
				$(CPP) $(CPPflags) $(INCLUDES) -c $<	-o $@

# # MAKEFILE
# # Define directories
# # IDIR =../include
# # ODIR = obj
# # LDIR = ../lib
# # Compiler and flags
# CPPflags = c++ -Wall
# # Name of exectuable
# PROG = project3.x
# # Dependencies (include files)
# # _DEPS = hellomake.h
# # DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# # Objects (.o files)
# _OBJ = hellomake.o hellofunc.o
# # OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
# # Libraries
# LIB = -larmadillo -llapack# -lbas
#
# # $(ODIR)/%.o:	%.cpp $(DEPS)
# # 	-c -o $@ $<
#
# $(PROG): $(OBJ)
# 	$(CPPflags) $(OBJ) $(LIB) -o $(PROG)
