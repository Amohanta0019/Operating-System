#!/bin/bash

input_file="students.txt"
output_file="grades.txt"

# Check if input file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

# Process each record
while IFS=',' read -r roll name marks; do
  grade="F"
  case $marks in
    [9][0-9]|100) grade="O" ;; # Outstanding
    8[0-9]) grade="E" ;;      # Excellent
    7[0-9]) grade="A" ;;      # Good
    6[0-9]) grade="B" ;;      # Average
    5[0-9]) grade="C" ;;      # Pass
    *) grade="F" ;;           # Fail
  esac
  echo "$roll, $name, $marks, $grade" >> "$output_file"
done < "$input_file"

echo "Grades written to $output_file"
