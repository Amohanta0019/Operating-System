#!/bin/bash

# Prompt user to input the file name
read -p "Enter the file name: " file

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File not found!"
  exit 1
fi

# Read numbers and find greatest and lowest
numbers=$(cat "$file")
max=$(echo "$numbers" | tr ' ' '\n' | sort -n | tail -1)
min=$(echo "$numbers" | tr ' ' '\n' | sort -n | head -1)

echo "Greatest Number: $max"
echo "Lowest Number: $min"
