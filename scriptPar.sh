#!/bin/bash
#The proportion between asteroids and planets is 70/30
#Iterations are 50, 100, 200
#Sum of asteroids and planets is 250, 500 and 1000
g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 -fopenmp mainParallel.cpp -o mainPar


echo "---ITERATIONS: 50 ---"
for i in {0..14}
do
    ./mainPar 175 50 75 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 350 50 150 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 700 50 30 6
done
echo "---"

echo "---ITERATIONS: 100 ---"
for i in {0..14}
do
    ./mainPar 175 100 75 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 350 100 150 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 700 100 30 6
done
echo "---"

echo "---ITERATIONS: 200---"
for i in {0..14}
do
    ./mainPar 175 200 75 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 350 200 150 6
done
echo "---"

for i in {0..14}
do
    ./mainPar 700 200 30 6
done
echo "---"

echo "Dale Carla, ahora mostráme aunque sea una mijita de pezón"