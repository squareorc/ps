#!/bin/bash

# Taking input numbers
echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

# Addition
add=$((num1 + num2))
echo "Addition: $add"

# Subtraction
sub=$((num1 - num2))
echo "Subtraction: $sub"

# Multiplication
mul=$((num1 * num2))
echo "Multiplication: $mul"

# Division (integer division)
div=$((num1 / num2))
echo "Division (quotient): $div"

# Modulus (remainder)
mod=$((num1 % num2))
echo "Modulus (remainder): $mod"