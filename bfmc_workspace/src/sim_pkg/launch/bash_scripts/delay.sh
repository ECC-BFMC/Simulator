#!/bin/bash


file_namee=$(echo $3 | cut -d'.' -f 1)

echo   "******************************************************************"
echo   "******************************************************************"
printf "Spawning: %25s || Sleeping for: %2d seconds\n" $file_namee $1
echo   "******************************************************************"
echo   "******************************************************************"

# Sleep for the time specified in the 2nd argument of the argument list.
sleep $1

# Shift to the right the arguments list.
shift

roslaunch $@

