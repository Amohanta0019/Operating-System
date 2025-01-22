#!/bin/bash

# Prompt user to input directory path
read -p "Enter the directory path: " dir

output_file="file_list.txt"

# Check if directory exists
if [ -d "$dir" ]; then
  file_count=$(ls -1 "$dir" | wc -l)  # Count files
  echo "Number of files: $file_count" > "$output_file"
  echo "Files:" >> "$output_file"
  ls "$dir" >> "$output_file"         # Save file names to output file
  cat "$output_file"                  # Display the output
else
  echo "Directory not found!"
fi
