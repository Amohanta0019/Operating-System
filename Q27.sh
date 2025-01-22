#!/bin/bash

input_file="numbers.txt"

# Check if file exists
if [ ! -f "$input_file" ]; then
  echo "Input file '$input_file' not found!"
  exit 1
fi

echo "Palindrome numbers from the file:"
while read -r num; do
  reversed=$(echo "$num" | rev)
  if [ "$num" -eq "$reversed" ]; then
    echo "$num"
  fi
done < "$input_file"
