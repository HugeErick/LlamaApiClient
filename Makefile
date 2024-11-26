CC = gcc
CFLAGS = -Wall -Wextra -ggdb
LIBS = -lcurl -lcjson

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/llamaApiClient

.PHONY: all clean run 

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

set_env:
	@read -p "Enter your GROG_CLOUD_API_DEV_TOKEN: " token; \
	echo "export GROG_CLOUD_API_DEV_TOKEN=$$token" >> ~/.bashrc; \
	source ~/.bashrc

