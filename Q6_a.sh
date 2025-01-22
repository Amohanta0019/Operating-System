#!/bin/bash

# Shell script to check Armstrong numbers from a list of numbers

for num in "$@"; do
  original=$num
  sum=0
  length=${#num}  # Find the number of digits

  # Calculate the sum of the digits raised to the power of the length
  while [ $num -gt 0 ]; do
    digit=$((num % 10))
    sum=$((sum + digit**length))
    num=$((num / 10))
  done

  # Check if the number is an Armstrong number
  if [ "$sum" -eq "$original" ]; then
    echo "$original is an Armstrong number"
  else
    echo "$original is not an Armstrong number"
  fi
done
