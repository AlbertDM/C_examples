CC = gcc
CFLAGS = -Wall -Wextra -pthread
DEBUG_CFLAGS = -g

TARGET = producer_consumer

all: $(TARGET)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

$(TARGET): producerconsumer_01.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all debug clean

