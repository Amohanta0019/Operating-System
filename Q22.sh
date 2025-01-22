#!/bin/bash

for item in "$@"; do
  if [ -d "$item" ]; then
    echo "$item is a directory."
  elif [ -f "$item" ]; then
    echo "$item is a file."
    lines=$(wc -l < "$item")
    words=$(wc -w < "$item")
    echo "File '$item' has $lines lines and $words words."

    # Check group write permission
    if [ ! -w "$item" ]; then
      echo "Group does not have write permission. Adding it..."
      chmod g+w "$item"
    else
      echo "Group has write permission. Removing it..."
      chmod g-w "$item"
    fi
  else
    echo "$item is neither a file nor a directory."
  fi
done
