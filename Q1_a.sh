#!/bin/bash

# Function to calculate factorial
factorial() {
    local n=$1
    local fact=1
    for (( i=1; i<=n; i++ )); do
        fact=$((fact * i))
    done
    echo $fact
}

# Read input from user
read -p "Enter the value of x: " x
read -p "Enter the number of terms in the series: " n

# Initialize variables
result=0
power=1

# Calculate the series
for (( i=1; i<=n; i++ )); do
    if (( i % 2 == 1 )); then # Only calculate for odd terms (x, x^2/2!, x^4/4!, etc.)
        fact=$(factorial $power)
        term=$(echo "scale=5; $x^$power / $fact" | bc)
        result=$(echo "scale=5; $result + $term" | bc)
    fi
    power=$((power + 2))
done

echo "The result of the series is: $result"
