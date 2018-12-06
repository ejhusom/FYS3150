# =============================================
# Title:           MAKEFILE
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-09-27
# Version:         0.1
# =============================================
EXEC 			= runproject5.exe
CPP 			= c++
CPPflags 	= -Wall -O3 -g
LIB 			=

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
	@mkdir -p $(BUILD_DIR)
	@$(CPP) $(CPPFLAGS) $(INC_DIR) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@rm -rf $(OBJ) $(EXEC) $(BUILD_DIR)
	@echo "Cleanup complete!"

removedat:
	@rm -f *.dat
	@echo ".dat-files removed!"
