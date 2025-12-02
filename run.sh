#!/bin/bash
set -e

APP="terrain"

SRC="./Src/main.cpp \
    ./Src/Game/*.cpp \
    ./Src/Graphics/*.cpp \
    ./Src/Misc/*.cpp \
    ./Vendor/imgui-1.92.4/*.cpp \
    ./Vendor/imgui-1.92.4/backends/imgui_impl_glfw.cpp \
    ./Vendor/imgui-1.92.4/backends/imgui_impl_opengl3.cpp"

echo "BUILD: Compiling..."

g++ -std=c++2a $SRC -o $APP \
-I/usr/local/include \
-I/usr/include \
-L/usr/local/lib \
-L/usr/lib/x86_64-linux-gnu \
-I./Vendor/stb \
-I./Vendor/imgui-1.92.4 \
-I./Vendor/imgui-1.92.4/backends \
-lglfw -lGLEW -lGL -lassimp -lm -ldl -lpthread -Wl,-rpath,/usr/local/lib -lstdc++fs

if [ $? -eq 0 ]; then
    echo "BUILD: Compilation successful."
    echo "BUILD: Running..."
    ./terrain
else
    echo "BUILD: Error in compilation."
fi
