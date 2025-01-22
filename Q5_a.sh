#!/bin/bash

# Shell script to find palindrome words from a file

read -p "Enter the file name: " file

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File not found!"
  exit 1
fi

# Process the file and find palindrome words
echo "Palindrome words in the file:"
while read -r word; do
  # Remove special characters (.;,) and check for palindromes
  cleaned_word=$(echo "$word" | tr -d '.;,')
  reverse_word=$(echo "$cleaned_word" | rev)
  if [ "$cleaned_word" == "$reverse_word" ]; then
    echo "$cleaned_word"
  fi
done < "$file"
