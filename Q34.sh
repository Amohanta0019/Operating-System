#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Error: Provide a list of numbers as command-line arguments."
  exit 1
fi

echo "Palindrome numbers from the input:"
for num in "$@"; do
  reversed=$(echo "$num" | rev)
  if [ "$num" -eq "$reversed" ]; then
    echo "$num"
  fi
done
