CC = gcc
CFLAGS = -Wall -Wextra -ggdb
LIBS = -lcurl -lcjson
INCLUDE_DIRS = -I/usr/local/include -I/usr/include

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/llamaApiClient

.PHONY: all clean run check_deps

all: check_deps $(TARGET)

# Add instructions to guide the installation
install: check_deps
	@echo "Installing dependencies based on the detected platform."
	@if [ "$(OS)" = "Windows_NT" ]; then \
		./set_all_windows.bat; \
	elif [ "$(shell uname)" = "Darwin" ]; then \
		./set_all_mac.sh; \
	else \
		./set_all_unix.sh; \
	fi

set_env: install

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

set_env:
	@if [ "$(OS)" = "Windows_NT" ]; then \
		./set_all_windows.bat; \
	elif [ "$(shell uname)" = "Darwin" ]; then \
		./set_all_mac.sh; \
	else \
		./set_all_unix.sh; \
	fi
