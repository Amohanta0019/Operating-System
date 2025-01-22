#!/bin/bash

input_file="students.txt"

# Check if file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

read -p "Enter the number of new records to add: " n

for ((i = 1; i <= n; i++)); do
  read -p "Enter Roll: " roll
  read -p "Enter Name: " name
  read -p "Enter Marks: " marks
  echo "$roll | $name | $marks" >> "$input_file"
done

# Sort by marks
sort -t "|" -k3 -n "$input_file" -o "$input_file"

echo "Records added and sorted by marks:"
cat "$input_file"
