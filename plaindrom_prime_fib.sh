#!/bin/bash

echo "Enter a number:"
read num

# 1️⃣ Check Palindrome
rev=0
temp=$num

while [ $temp -gt 0 ]
do
    rem=$((temp % 10))
    rev=$((rev * 10 + rem))
    temp=$((temp / 10))
done

if [ $num -eq $rev ]; then
    echo "$num is a Palindrome number"
else
    echo "$num is NOT a Palindrome number"
fi


# 2️⃣ Check Prime
flag=0
if [ $num -le 1 ]; then
    flag=1
else
    for (( i=2; i<=num/2; i++ ))
    do
        if [ $((num % i)) -eq 0 ]; then
            flag=1
            break
        fi
    done
fi

if [ $flag -eq 0 ]; then
    echo "$num is a Prime number"
else
    echo "$num is NOT a Prime number"
fi


# 3️⃣ Generate Fibonacci Series up to n terms
echo "Enter how many terms of Fibonacci series you want:"
read n

a=0
b=1
echo "Fibonacci Series:"
echo -n "$a $b "

for (( i=2; i<n; i++ ))
do
    fib=$((a + b))
    echo -n "$fib "
    a=$b
    b=$fib
done

echo