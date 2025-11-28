#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <iostream>
#include <vector>
#include "./VAO.hpp"
#include "./VBO.hpp"
#include "./Vertex.hpp"

class Cubemap
{
private:
    VAO vao;
    VBO vbo;
    VBO ebo;
    unsigned int textureID;

    std::vector<float> vertices = {
        -1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        1.0f,
        -1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        -1.0f,
        1.0f,
        1.0f,
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        0, 3, 7,
        7, 4, 0,

        1, 5, 6,
        6, 2, 1,

        4, 7, 6,
        6, 5, 4,

        3, 2, 6,
        6, 7, 3,

        0, 4, 5,
        5, 1, 0};

    std::vector<std::string> faces = {
        "./Resources/Cubemaps/right.jpg",
        "./Resources/Cubemaps/left.jpg",
        "./Resources/Cubemaps/top.jpg",
        "./Resources/Cubemaps/bottom.jpg",
        "./Resources/Cubemaps/front.jpg",
        "./Resources/Cubemaps/back.jpg"};

public:
    Cubemap();
    void setBuffers();
    void render();
};

#endif