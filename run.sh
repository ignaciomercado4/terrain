#!/bin/bash

APP="terrain"

SRC="*.cpp"

echo "Compiling $SRC ..."
g++ $SRC -o $APP -lglfw -lGLEW -lGL -lm -I./Vendor

if [ $? -eq 0 ]; then
    echo "Compilation succesful."
    echo "Running..."
    ./terrain
else
    echo "Error in compilation."
fi