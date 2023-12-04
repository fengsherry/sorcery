#!/bin/bash
# Usage:
# set permissions:
#   chmod +x run_program.sh
# execute
#   ./run_program.sh input_file


# Read the first line from the file (command line arguments)
read -r args < "$1"


# Read the remaining lines from the file and pass them as input
tail -n +2 "$1" | ./sorcery $args

