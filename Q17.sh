#!/bin/bash

input_file="students.txt"
temp_file="temp.txt"

# Check if input file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

# Display records
echo "Current Records:"
cat "$input_file"

# Prompt user for roll number and new marks
read -p "Enter roll number to update: " roll
read -p "Enter new marks: " new_marks

# Update marks
updated=false
while IFS=',' read -r r name marks; do
  if [ "$r" == "$roll" ]; then
    echo "$r, $name, $new_marks" >> "$temp_file"
    updated=true
  else
    echo "$r, $name, $marks" >> "$temp_file"
  fi
done < "$input_file"

if $updated; then
  mv "$temp_file" "$input_file"
  echo "Marks updated successfully!"
else
  echo "Roll number not found!"
  rm "$temp_file"
fi
