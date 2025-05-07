#!/bin/bash

# $1 = first number
# $2 = operator
# $3 = second number

if [ $# -ne 3 ]; then
  echo "Usage: $0 number1 operator number2"
  exit 1
fi

num1=$1
op=$2
num2=$3

case $op in
  +)
    result=$((num1 + num2))
    ;;
  -)
    result=$((num1 - num2))
    ;;
  \*)
    result=$((num1 * num2))
    ;;
  /)
    if [ $num2 -eq 0 ]; then
      echo "Division by zero not allowed!"
      exit 1
    fi
    result=$((num1 / num2))
    ;;
  %)
    result=$((num1 % num2))
    ;;
  *)
    echo "Invalid operator! Use +, -, *, /, or %"
    exit 1
    ;;
esac

echo "Result: $result"