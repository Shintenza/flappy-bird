CC = g++
CFLAGS = -Wall
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
HEADERS = $(wildcard $(SRC)/include/*.hpp)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
BIN_DIR = bin
BIN = $(BIN_DIR)/flappy_bird

all: $(BIN)
$(BIN): $(OBJS) | structure
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS) | structure
	$(CC) $(CFLAGS) -c $< -o $@	$(LDFLAGS)
structure:
	mkdir -p $(OBJ) $(BIN_DIR)
run: all
	./$(BIN)
clean:
	rm -rf $(BIN_DIR)/* $(OBJ)/*
