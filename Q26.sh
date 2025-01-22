#!/bin/bash

input_file="students.txt"

# Check if file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

echo "Current records in the file:"
cat "$input_file"

read -p "Enter the Roll number of the record to delete: " roll

# Delete the record
grep -v "^$roll" "$input_file" > temp_file && mv temp_file "$input_file"

echo "Record deleted successfully! Updated records:"
cat "$input_file"
