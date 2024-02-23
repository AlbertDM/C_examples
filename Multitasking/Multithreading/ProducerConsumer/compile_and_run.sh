#!/bin/bash

# Usecase options
# ./compile_and_run.sh              # Compile and run without debugging
# ./compile_and_run.sh --debug       # Compile with debugging and run with GDB
# ./compile_and_run.sh -d            # Short form for debugging option
# ./compile_and_run.sh --help        # Display help message


# Default compilation options
COMPILATION_OPTIONS=""

# Check if the user provided any options
if [ "$#" -gt 0 ]; then
    case "$1" in
        -d|--debug)
            # Debugging option
            COMPILATION_OPTIONS="-g"
            shift  # Consume the option
            ;;
        -h|--help)
            # Display help and exit
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  -d, --debug   Compile with debugging information and run with GDB"
            echo "  -h, --help    Display this help message"
            exit 0
            ;;
        *)
            # Unknown option
            echo "Unknown option: $1"
            echo "Use '$0 --help' for usage information."
            exit 1
            ;;
    esac
fi

# Compile the program
gcc $COMPILATION_OPTIONS -Wall -Wextra -pthread -o producerconsumer_01 producerconsumer_01.c

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Check if debugging is enabled
    if [ "$COMPILATION_OPTIONS" == "-g" ]; then
        # Run with GDB
        gdb -ex run --args ./producerconsumer_01
    else
        # Run without GDB
        ./producerconsumer_01
    fi
else
    echo "Compilation failed."
fi

