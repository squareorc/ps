#!/bin/bash

echo "Choose conversion:"
echo "1. Decimal to Binary"
echo "2. Binary to Decimal"
read choice

case $choice in
  1)
    echo "Enter a decimal number:"
    read dec
    bin=""
    while [ $dec -gt 0 ]
    do
      rem=$((dec % 2))
      bin="$rem$bin"
      dec=$((dec / 2))
    done
    echo "Binary: $bin"
    ;;
  2)
    echo "Enter a binary number:"
    read bin
    dec=0
    power=0
    len=${#bin}

    for (( i=$len-1; i>=0; i-- ))
    do
      digit=${bin:$i:1}
      if [ $digit -eq 1 ]; then
        dec=$((dec + 2**power))
      fi
      power=$((power+1))
    done
    echo "Decimal: $dec"
    ;;
  *)
    echo "Invalid choice!"
    ;;
esac