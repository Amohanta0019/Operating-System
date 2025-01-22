#!/bin/bash

if [ $# -lt 5 ]; then
  echo "Error: Provide 5 numbers as arguments."
  exit 1
fi

sum=0
for num in "$@"; do
  sum=$((sum + num))
done

echo "The sum of the numbers is: $sum"
