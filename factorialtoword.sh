#!/bin/bash

# Function to convert number to words
number_to_words() {
    num=$1

    units=("zero" "one" "two" "three" "four" "five" "six" "seven" "eight" "nine")
    teens=("ten" "eleven" "twelve" "thirteen" "fourteen" "fifteen" "sixteen" "seventeen" "eighteen" "nineteen")
    tens=("" "" "twenty" "thirty" "forty" "fifty" "sixty" "seventy" "eighty" "ninety")

    if [ $num -lt 10 ]; then
        echo -n "${units[$num]}"
    elif [ $num -lt 20 ]; then
        echo -n "${teens[$((num-10))]}"
    elif [ $num -lt 100 ]; then
        echo -n "${tens[$((num/10))]}"
        if [ $((num%10)) -ne 0 ]; then
            echo -n " ${units[$((num%10))]}"
        fi
    elif [ $num -lt 1000 ]; then
        echo -n "${units[$((num/100))]} hundred"
        if [ $((num%100)) -ne 0 ]; then
            echo -n " and "
            number_to_words $((num%100))
        fi
    elif [ $num -lt 10000 ]; then
        echo -n "${units[$((num/1000))]} thousand"
        if [ $(( (num%1000) )) -ne 0 ]; then
            echo -n " "
            number_to_words $((num%1000))
        fi
    else
        echo -n "Number too big for this demo"
    fi
}

# Factorial calculation
echo "Enter a number:"
read num

fact=1

for (( i=1; i<=num; i++ ))
do
    fact=$((fact * i))
done

echo "Factorial of $num is: $fact"
echo -n "In words: "
number_to_words $fact
echo