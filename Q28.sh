#!/bin/bash

file_count=$(ls -1 | wc -l)
largest_file=$(ls -S | head -1)

echo "Number of files in the current directory: $file_count"
echo "Largest file: $largest_file"
