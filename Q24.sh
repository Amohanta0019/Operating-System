#!/bin/bash

read -p "Enter lower range: " lower
read -p "Enter upper range: " upper

is_prime() {
  local num=$1
  if [ "$num" -le 1 ]; then
    return 1
  fi
  for ((i = 2; i * i <= num; i++)); do
    if [ $((num % i)) -eq 0 ]; then
      return 1
    fi
  done
  return 0
}

echo "Prime numbers between $lower and $upper:"
for ((num = lower; num <= upper; num++)); do
  if is_prime "$num"; then
    echo "$num"
  fi
done
