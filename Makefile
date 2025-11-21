# === COMPILER & FLAGS ===
CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c99 -Iinclude -g
LDFLAGS := 
SRC_DIR := src
OBJ_DIR := obj
BIN     := gsh

# === FILES ===
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# === DEFAULT TARGET ===
all: $(BIN)

# === LINKING ===
$(BIN): $(OBJ)
	@echo "Linking executable: $@"
	@$(CC) $(OBJ) -o $@ $(LDFLAGS)

# === COMPILING ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# === CREATE OBJ DIR IF NEEDED ===
$(OBJ_DIR):
	@mkdir -p $@

# === CLEANING ===
.PHONY: clean rebuild run

clean:
	@echo "Cleaning build files..."
	@rm -rf $(OBJ_DIR) $(BIN)

rebuild: clean all

run: all
	@echo "Running shell..."
	@./$(BIN)