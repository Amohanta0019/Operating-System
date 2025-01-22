#!/bin/bash

# Check if file is supplied as an argument
if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

file="$1"
output_file="weather_report.txt"

# Check if file exists
if [ ! -f "$file" ]; then
  echo "File not found!"
  exit 1
fi

> "$output_file"  # Clear the output file

# Process the input file
while IFS=',' read -r day temperature; do
  if [ "$temperature" -lt 15 ]; then
    weather="Very Cold"
  elif [ "$temperature" -ge 15 ] && [ "$temperature" -lt 25 ]; then
    weather="Cold"
  elif [ "$temperature" -ge 25 ] && [ "$temperature" -lt 35 ]; then
    weather="Hot"
  else
    weather="Very Hot"
  fi
  echo "$day: $weather" >> "$output_file"
done < "$file"

echo "Weather report saved in $output_file"
