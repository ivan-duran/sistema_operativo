# Variables
CXX = g++
CXXFLAGS = -I./include -Wall -std=c++11
SRC = ./src/count_words.cpp ./src/options.cpp ./src/utils.cpp
OBJ_DIR = ./object
OBJ = $(SRC:./src/%.cpp=$(OBJ_DIR)/%.o)
TARGET = count_words

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(OBJ_DIR)/%.o: ./src/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
