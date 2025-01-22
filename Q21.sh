#!/bin/bash

# Function to calculate GCD
gcd() {
  local a=$1
  local b=$2
  while [ $b -ne 0 ]; do
    local temp=$b
    b=$((a % b))
    a=$temp
  done
  echo $a
}

# Function to calculate LCM
lcm() {
  local a=$1
  local b=$2
  echo $(( (a * b) / $(gcd $a $b) ))
}

read -p "Enter first number: " num1
read -p "Enter second number: " num2

echo "GCD: $(gcd $num1 $num2)"
echo "LCM: $(lcm $num1 $num2)"
