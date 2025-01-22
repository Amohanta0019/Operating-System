#!/bin/bash

# Shell script to calculate the first n Fibonacci numbers and store them in a file 

read -p "Enter the number of Fibonacci terms to generate: " n
output_file="fibonacci_output.txt"

# Initialize the first two Fibonacci numbers
a=0
b=1

# Clear the output file
> $output_file

# Generate the Fibonacci series
echo "Fibonacci series:" > $output_file
for ((i=1; i<=n; i++)); do
  echo -n "$a " >> $output_file  # Append the current term to the file
  next=$((a + b))
  a=$b
  b=$next
done

echo -e "\nFibonacci series written to $output_file"
