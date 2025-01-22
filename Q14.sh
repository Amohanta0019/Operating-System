#!/bin/bash

# Prompt user for x and n
read -p "Enter value of x: " x
read -p "Enter value of n: " n

# Calculate Y(x, n)
if [ "$n" -eq 1 ]; then
  y=$((1 + x * x))
elif [ "$n" -eq 2 ]; then
  y=$((1 + x / n))
elif [ "$n" -eq 3 ]; then
  y=$((1 + 2 * x))
else
  y=$((1 + n * x))
fi

echo "Y(x, n) = $y"
