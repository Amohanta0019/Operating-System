#!/bin/bash

read -p "Enter the filename: " file

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File not found!"
  exit 1
fi

# Display current permissions
echo "Current permissions for $file:"
ls -l "$file"

# Change permissions
echo "Changing permissions for $file..."
chmod u+rwx,g+rw,o+r "$file"

# Display updated permissions
echo "Updated permissions for $file:"
ls -l "$file"
