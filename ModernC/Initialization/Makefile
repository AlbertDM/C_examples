CC = gcc
# Default STD version
STD ?= c99
# User STD version
CFLAGS = -std=$(STD) -Wall -Wextra -pedantic

# List of source files
SRC_FILES = example1.c example_TCP_IP_MQTT.c

# List of object files for each executable
OBJ_FILES = $(SRC_FILES:%.c=%_$(STD).o)

# List of corresponding executable names
EXE_FILES = $(SRC_FILES:%.c=%_$(STD))

all: $(EXE_FILES)

# Build specific object file
%_$(STD).o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Link specific executable (explicitly specify object file)
%_$(STD): %_$(STD).o
	$(CC) $(CFLAGS) -o $@ $<

# Build individual object file (implicitly included in %.o and %_$(STD))
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Build individual executable based on source file (explicitly specify object file)
example1: example1_$(STD).o
	$(CC) $(CFLAGS) -o $@ $<

example_TCP_IP_MQTT: example_TCP_IP_MQTT_$(STD).o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE_FILES) $(OBJ_FILES)

# Clean all object files and executables (regardless of STD)
cleanall: clean
	rm -f *.o

# Example usage:
# make clean STD=c17 # Cleans all C17-related files
# make example1 STD=c17 # Creates example1_c17.o and example1_c17
# make clean # Cleans all object files and executables
