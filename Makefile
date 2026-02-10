TARGET_EXEC := main

CC := gcc
CFLAGS := -Wall -Wextra

BUILD_DIR := ./build

SRC := $(wildcard *.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all clean
all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) -o $@

clean:
	rm -rf $(BUILD_DIR)