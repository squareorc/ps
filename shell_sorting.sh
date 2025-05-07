#!/bin/bash

echo "Enter numbers separated by space:"
read -a arr

n=${#arr[@]}

# Bubble sort logic
for (( i=0; i<$n; i++ ))
do
  for (( j=0; j<$n-i-1; j++ ))
  do
    if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
    then
      # Swap
      temp=${arr[j]}
      arr[$j]=${arr[$((j+1))]}
      arr[$((j+1))]=$temp
    fi
  done
done

echo "Sorted numbers: ${arr[@]}"