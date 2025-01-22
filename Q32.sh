#!/bin/bash

input_file="students.txt"

# Check if file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

echo "Current records in the file:"
cat "$input_file"

read -p "Enter the Roll number of the student to update marks: " roll

# Check if the roll exists
if ! grep -q "^$roll" "$input_file"; then
  echo "Roll number $roll not found!"
  exit 1
fi

read -p "Enter the new marks: " new_marks

# Update the marks
awk -v roll="$roll" -v marks="$new_marks" -F "|" '
BEGIN { OFS=" | " }
{
  if ($1 == roll) $3 = marks
  print $0
}' "$input_file" > temp_file && mv temp_file "$input_file"

echo "Marks updated successfully! Updated records:"
cat "$input_file"
