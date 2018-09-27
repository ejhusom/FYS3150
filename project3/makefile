# =============================================
# Title:           MAKEFILE
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-09-27
# Version:         0.1
# =============================================
EXEC 			= project2.x
CPP 			= c++
CPPflags 	= -Wall -O3
LIB = -larmadillo -llapack -lblas

SRC_DIR		= ./src
INC_DIR		= -I./include
BUILD_DIR	= ./build

SRC 			:= $(wildcard $(SRC_DIR)/*.cpp)
INC  			:= $(wildcard $(SRC_DIR)/*.h)
OBJ				:= $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
#====================================================
$(EXEC): $(OBJ)
	@$(CPP) $(OBJ) $(LIB) -o $@
	@echo "Linking complete!"
	@echo $(EXEC) "ready to run!"

$(OBJ): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CPP) $(CPPFLAGS) $(INC_DIR) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@rm -f $(OBJ) $(EXEC)
	@echo "Cleanup complete!"

removedat:
	@rm -f *.dat
	@echo ".dat-files removed!"
