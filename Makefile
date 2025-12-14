CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O1

SRC_DIR = src
BIN_DIR = bin
OUT_DIR = out
INCLUDE_DIR = include

SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))
 
TARGET = $(BIN_DIR)/baccarat

all: $(TARGET) $(OUT_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OUT_DIR)

install:
	cp $(TARGET) /usr/local/bin

build-debug:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) -g -gdwarf-4" all

run:
	$(MAKE) clean
	$(MAKE) all
	$(TARGET) --num-shoes 10 --strategy random > out/random.txt
	$(TARGET) --num-shoes 10 --strategy doubling > out/doubling.txt
	$(TARGET) --num-shoes 10 --strategy martingale > out/martingale.txt
	python -m graphing.graph_result $(OUT_DIR)

.PHONY: all clean install build-debug run
