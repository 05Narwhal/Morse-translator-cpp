#!/bin/bash

# Array to store the names of .cpp files
cpp_files=()

# Find all .cpp files in the current directory and its subdirectories
for file in lib/*.cpp; do
    cpp_files+=("$file")
done

# Compile with g++
compileCmd="g++ -std=c++20 main.cpp "${cpp_files[*]}" -o prog"
echo "\
--Command: $compileCmd \
"

$compileCmd

if [ $? -eq 0 ]; then
    echo "==== Compilation successful. Running the program... ==== \
    "
    # Run the compiled program
    ./prog
else
    echo "==== Compilation failed. ===="
fi