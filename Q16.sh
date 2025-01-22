#!/bin/bash

# Prompt user for a date
read -p "Enter a date (YYYY-MM-DD): " date

# Validate the date
if date -d "$date" >/dev/null 2>&1; then
  echo "The date is valid."
else
  echo "The date is invalid."
fi
