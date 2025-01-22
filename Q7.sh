#!/bin/bash

# Check if at least one file is provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 <file1> <file2> ..."
  exit 1
fi

# Loop through each file provided
for file in "$@"; do
  if [ -f "$file" ]; then
    echo "File: $file"
    echo "Characters: $(wc -c < "$file")"
    echo "Words: $(wc -w < "$file")"
    echo "Lines: $(wc -l < "$file")"
    echo "--------------------------"
  else
    echo "$file is not a valid file."
  fi
done
