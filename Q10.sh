#!/bin/bash

# Prompt user to input the file name
read -p "Enter input file name: " file

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File not found!"
  exit 1
fi

highest_marks=0
top_student=""

# Read the file line by line
while IFS='|' read -r roll name marks; do
  if [ "$marks" -gt "$highest_marks" ]; then
    highest_marks=$marks
    top_student="Roll: $roll, Name: $name"
  fi
done < "$file"

echo "Top Student: $top_student"
echo "Highest Marks: $highest_marks"
