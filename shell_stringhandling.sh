#!/bin/bash

# Taking input strings
echo "Enter first string:"
read str1

echo "Enter second string:"
read str2

# String Length
echo "Length of first string is: ${#str1}"

# Concatenation
concat="$str1$str2"
echo "Concatenated string: $concat"

# Substring extraction (from position 2, length 4)
substr=${str1:2:4}
echo "Substring of first string (from position 2, length 4): $substr"

# String comparison
if [ "$str1" = "$str2" ]; then
    echo "Both strings are equal"
else
    echo "Strings are not equal"
fi

# Changing to uppercase (using tr)
echo "First string in uppercase: $(echo $str1 | tr 'a-z' 'A-Z')"

# Changing to lowercase (using tr)
echo "Second string in lowercase: $(echo $str2 | tr 'A-Z' 'a-z')"