#!/bin/bash

read -p "Enter the first directory: " dir1
read -p "Enter the second directory: " dir2

# Check if both directories exist
if [ ! -d "$dir1" ] || [ ! -d "$dir2" ]; then
  echo "One or both directories do not exist!"
  exit 1
fi

count1=$(ls -1 "$dir1" | wc -l)
count2=$(ls -1 "$dir2" | wc -l)

if [ "$count1" -gt "$count2" ]; then
  echo "Directory $dir1 has more files ($count1) than $dir2 ($count2)."
else
  echo "Directory $dir2 has more files ($count2) than $dir1 ($count1)."
fi
