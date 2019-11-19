#!/bin/bash

g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 main.cpp -o main


echo "---"
for i in {0..14}
do
    ./main    250 50 250 6
done
echo "---"
for i in {0..14}
do
    ./main    250 100 250 6
done
echo "---"
for i in {0..14}
do
    ./main    250 200 250 6
done
echo "---"
for i in {0..14}
do
    ./main    500 50 500 6
done
echo "---"
for i in {0..14}
do
    ./main    500 100 500 6
done
echo "---"
for i in {0..14}
do
    ./main    500 200 500 6
done
echo "---"
for i in {0..14}
do
    ./main    1000 50 1000 6
done
echo "---"
for i in {0..14}
do
    ./main    1000 100 1000 6
done
echo "---"
for i in {0..14}
do
    ./main    1000 200 1000 6
done
