#!/bin/bash

APP="terrain"

SRC="*.cpp"

echo "BUILD: Compiling $SRC ..."
g++ $SRC -o $APP -lglfw -lGLEW -lGL -lm -I./Vendor

if [ $? -eq 0 ]; then
    echo "BUILD: Compilation succesful."
    echo "BUILD: Running..."
    ./terrain
else
    echo "BUILD: Error in compilation."
fi