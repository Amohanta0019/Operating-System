#!/bin/bash

# Shell script to find palindrome numbers from a list of numbers . Input: List of numbers passed as command-line arguments

for num in "$@"; do
  # Reverse the number
  reverse=$(echo "$num" | rev)

  # Check if the number is a palindrome
  if [ "$num" -eq "$reverse" ]; then
    echo "$num is a palindrome"
  else
    echo "$num is not a palindrome"
  fi
done
