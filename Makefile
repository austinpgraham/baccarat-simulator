CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O1

SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))
 
TARGET = $(BIN_DIR)/baccarat

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

install:
	cp $(TARGET) /usr/local/bin

.PHONY: all clean install
