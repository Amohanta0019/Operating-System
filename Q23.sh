#!/bin/bash

input_file="students.txt"

# Check if file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

read -p "Enter number of new records to add: " n

for ((i = 1; i <= n; i++)); do
  read -p "Enter Roll: " roll
  read -p "Enter Name: " name
  read -p "Enter Marks: " marks
  echo "$roll | $name | $marks" >> "$input_file"
done

echo "Records added successfully!"
