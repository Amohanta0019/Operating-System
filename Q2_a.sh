#!/bin/bash

# Shell script to calculate the series: 1 + (x/2)² − (x/2)³ + (x/2)⁴ − (x/2)⁵ ...
# Input: x (value for the series), n (number of terms)

read -p "Enter the value of x: " x
read -p "Enter the number of terms (n): " n

sum=1  # Initialize sum with the first term (1)
sign=-1  # To alternate between positive and negative terms

for ((i=2; i<=n; i++)); do
  # Calculate (x/2)^i
  power=1
  for ((j=1; j<=i; j++)); do
    power=$((power * x / 2))
  done

  # Add or subtract the term based on the alternating sign
  term=$((sign * power))
  sum=$((sum + term))

  # Flip the sign for the next term
  sign=$((sign * -1))
done

echo "The sum of the series is: $sum"
